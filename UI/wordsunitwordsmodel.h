#ifndef WORDSUNITWORDSMODEL_H
#define WORDSUNITWORDSMODEL_H

#include <QAbstractTableModel>
#include "ViewModels/vmwordsunit.h"

class WordsUnitWordsModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit WordsUnitWordsModel(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    const VMWordsUnit* vmWordsUnit = nullptr;
private:
};

#endif // WORDSUNITWORDSMODEL_H
