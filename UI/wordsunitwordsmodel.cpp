#include "wordsunitwordsmodel.h"
#include "wordsunitwindow.h"

WordsUnitWordsModel::WordsUnitWordsModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

QVariant WordsUnitWordsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole || orientation != Qt::Horizontal)
         return QVariant();

    switch (section) {
    case 0: return QVariant(QString("UNIT"));
    case 1: return QVariant(QString("PART"));
    case 2: return QVariant(QString("SEQNUM"));
    case 3: return QVariant(QString("WORD"));
    case 4: return QVariant(QString("NOTE"));
    case 5: return QVariant(QString("ACCURACY"));
    case 6: return QVariant(QString("WORDID"));
    case 7: return QVariant(QString("ID"));
    default: return QVariant();
    }
}

int WordsUnitWordsModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid() || !vmWordsUnit)
        return 0;

    return vmWordsUnit->unitwords.size();
}

int WordsUnitWordsModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid() || !vmWordsUnit)
        return 0;

    return 8;
}

QVariant WordsUnitWordsModel::data(const QModelIndex &index, int role) const
{
    if (role != Qt::DisplayRole || !index.isValid())
        return QVariant();

    const auto& o = vmWordsUnit->unitwords[index.row()];
    switch (index.column()) {
    case 0: return QVariant(QString::fromStdString_t(o.UNITSTR()));
    case 1: return QVariant(QString::fromStdString_t(o.PARTSTR()));
    case 2: return QVariant(o.SEQNUM);
    case 3: return QVariant(QString::fromStdString_t(o.WORD));
    case 4: return QVariant(QString::fromStdString_t(o.NOTE));
    case 5: return QVariant(QString::fromStdString_t(o.ACCURACY()));
    case 6: return QVariant(o.WORDID);
    case 7: return QVariant(o.ID);
    default: return QVariant();
    }
}
