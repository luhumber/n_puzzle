#include "PuzzleParser.h"
#include <QRegularExpression>

PuzzleParser::PuzzleParser() 
    : _puzzle_size(0) {}

bool PuzzleParser::Parse(const QString &input)
{
    QTextStream stream(const_cast<QString*>(&input));

    if (!ReadPuzzleSize(stream))
        return false;
    
    _puzzle_vector.clear();
    
    if (!ReadPuzzleRows(stream))
        return false;
    

    if (CheckSolvability(_puzzle_vector, _puzzle_size)) {
        _is_solvable = true;
    } else {
        _is_solvable = false;
        return false;
    }
    return true;
}

QVector<int> snailOrder(int size) {
    QVector<int> order(size * size);
    int dx[] = {1, 0, -1, 0};
    int dy[] = {0, 1, 0, -1};
    int x = 0, y = 0, dir = 0, val = 0;
    QVector<QVector<bool>> visited(size, QVector<bool>(size, false));
    for (int i = 0; i < size * size; ++i) {
        order[y * size + x] = val++;
        visited[y][x] = true;
        int nx = x + dx[dir], ny = y + dy[dir];
        if (nx < 0 || nx >= size || ny < 0 || ny >= size || visited[ny][nx])
            dir = (dir + 1) % 4;
        x += dx[dir];
        y += dy[dir];
    }
    return order;
}

bool PuzzleParser::CheckSolvability(const QVector<int>& puzzle, int size) {
    QVector<int> snail = snailOrder(size);
    QHash<int, int> valueToSnailIndex;
    for (int i = 0; i < snail.size(); ++i)
        valueToSnailIndex[snail[i]] = i;

    QVector<int> remapped(puzzle.size());
    int emptySnailIndex = 0;
    for (int i = 0; i < puzzle.size(); ++i) {
        remapped[i] = valueToSnailIndex[puzzle[i]];
        if (puzzle[i] == 0)
            emptySnailIndex = valueToSnailIndex[0];
    }

    int inversions = 0;
    for (int i = 0; i < remapped.size(); i++) {
        if (remapped[i] == valueToSnailIndex[0])
            continue;
        for (int j = i + 1; j < remapped.size(); j++) {
            if (remapped[j] == valueToSnailIndex[0])
                continue;
            if (remapped[i] > remapped[j])
                inversions++;
        }
    }

    int emptyRowFromBottom = size - (emptySnailIndex / size);

    if (size % 2 == 1) {
        return inversions % 2 == 0;
    } else {
        return (emptyRowFromBottom % 2 == 1) ? (inversions % 2 == 0) : (inversions % 2 == 1);
    }
}

bool PuzzleParser::ReadPuzzleSize(QTextStream &stream)
{
    QString line;
    do {
        line = stream.readLine();
        if (line.isNull()) 
            return false;
    } while (line.trimmed().isEmpty() || line.trimmed().startsWith("#"));
    
    bool ok = false;
    _puzzle_size = line.toInt(&ok);
    return ok && _puzzle_size > 0;
}

bool PuzzleParser::ReadPuzzleRows(QTextStream &stream)
{
    int rowCount = 0;
    while (!stream.atEnd() && rowCount < _puzzle_size) {
        QString line = stream.readLine();

        if (line.isEmpty() || line.startsWith("#"))
            continue;

        int comment_index = line.indexOf('#');
        if (comment_index != -1)
            line = line.left(comment_index);

        QStringList parts = line.split(QRegularExpression("[ \t]+"), Qt::SkipEmptyParts);

        if (parts.size() != _puzzle_size)
            return false;

        for (const QString &part : parts) {
            bool is_number = false;
            int value = part.toInt(&is_number);

            if (!is_number)
                return false;

            _puzzle_vector.append(value); // Ajoute chaque valeur directement dans le QVector<int>
        }
        rowCount++;
    }

    return rowCount == _puzzle_size;
}
