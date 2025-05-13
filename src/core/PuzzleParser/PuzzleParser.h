#pragma once

#include <QString>
#include <QVector>
#include <QTextStream>

class PuzzleParser
{
public:
    PuzzleParser();
    ~PuzzleParser() = default;

    bool                Parse(const QString &input);
    int                 getPuzzleSize() const { return _puzzle_size; }
    bool                isSolvable() const { return _is_solvable; }
    const QVector<int>& getPuzzleVector() const { return _puzzle_vector; }
    
private:
    bool ReadPuzzleSize(QTextStream &stream);
    bool ReadPuzzleRows(QTextStream &stream);
    bool CheckSolvability(const QVector<int>& puzzle, int size);
    
    int             _puzzle_size;
    QVector<int>    _puzzle_vector;
    bool            _is_solvable;
};
