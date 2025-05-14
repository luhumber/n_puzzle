#include "PuzzleParser.h"
#include <QRegularExpression>

PuzzleParser::PuzzleParser() 
    : _puzzle_size(0) {}

bool PuzzleParser::Parse(const QString &input)
{
    QTextStream stream(const_cast<QString*>(&input));

    if (!this->ReadPuzzleSize(stream))
        return false;
    
    _puzzle_vector.clear();
    
    if (!this->ReadPuzzleRows(stream))
        return false;
    

    if (this->CheckSolvability(_puzzle_vector, _puzzle_size)) {
        _is_solvable = true;
    } else {
        _is_solvable = false;
        return false;
    }
    return true;
}

QVector<int> PuzzleParser::SnailOrder(int size) {
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
    QVector<int> snail = this->SnailOrder(size);
    QHash<int, int> value_to_snail_index;
    for (int i = 0; i < snail.size(); ++i)
        value_to_snail_index[snail[i]] = i;

    QVector<int> remapped(puzzle.size());
    int empty_snail_index = 0;
    for (int i = 0; i < puzzle.size(); ++i) {
        remapped[i] = value_to_snail_index[puzzle[i]];
        if (puzzle[i] == 0)
            empty_snail_index = value_to_snail_index[0];
    }

    int inversions = 0;
    for (int i = 0; i < remapped.size(); i++) {
        if (remapped[i] == value_to_snail_index[0])
            continue;
        for (int j = i + 1; j < remapped.size(); j++) {
            if (remapped[j] == value_to_snail_index[0])
                continue;
            if (remapped[i] > remapped[j])
                inversions++;
        }
    }

    int empty_row_from_bottom = size - (empty_snail_index / size);

    if (size % 2 == 1) {
        return inversions % 2 == 0;
    } else {
        return (empty_row_from_bottom % 2 == 1) ? (inversions % 2 == 0) : (inversions % 2 == 1);
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

bool PuzzleParser::IsValidPuzzle(const QVector<int>& values, int size)
{
    if (values.size() != size * size)
        return false;

    QSet<int> unique;
    for (int v : values)
        unique.insert(v);

    if (unique.size() != size * size)
        return false;

    for (int i = 0; i < size * size; ++i)
        if (!unique.contains(i))
            return false;

    return true;
}

bool PuzzleParser::ReadPuzzleRows(QTextStream &stream)
{
    QVector<int> values;
    int row_count = 0;

    while (!stream.atEnd() && row_count < _puzzle_size) {
        QString line = stream.readLine().split('#').first().trimmed();
        if (line.isEmpty())
            continue;

        QStringList parts = line.split(QRegularExpression("[ \t]+"), Qt::SkipEmptyParts);
        if (parts.size() != _puzzle_size)
            return false;

        for (const QString& part : parts) {
            bool ok = false;
            int value = part.toInt(&ok);
            if (!ok)
                return false;
            values.append(value);
        }
        row_count++;
    }

    if (row_count != _puzzle_size)
        return false;

    if (!this->IsValidPuzzle(values, _puzzle_size))
        return false;

    _puzzle_vector = values;
    return true;
}
