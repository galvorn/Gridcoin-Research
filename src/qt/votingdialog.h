#ifndef VOTINGDIALOG_H
#define VOTINGDIALOG_H

#include <time.h>
#include <QAbstractTableModel>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QList>
#include <QModelIndex>
#include <QPoint>
#include <QSortFilterProxyModel>
#include <QString>
#include <QStringList>
#include <QTableView>
#include <QListWidget>
#include <QListWidgetItem>

#include <QtGlobal>
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
#  include <QtWidgets>
#else
#  include <QtGui>
#endif

#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
#include <QtCharts/QChartGlobal>
#endif

QT_BEGIN_NAMESPACE
class QEvent;
class QObject;
class QResizeEvent;
QT_END_NAMESPACE

QT_CHARTS_BEGIN_NAMESPACE
class QChart;
QT_CHARTS_END_NAMESPACE

#define VOTINGDIALOG_WIDTH_RowNumber          40
#define VOTINGDIALOG_WIDTH_Title              225
#define VOTINGDIALOG_WIDTH_Expiration         175
#define VOTINGDIALOG_WIDTH_ShareType          80
#define VOTINGDIALOG_WIDTH_Question           140
#define VOTINGDIALOG_WIDTH_Answers            80
#define VOTINGDIALOG_WIDTH_TotalParticipants  80
#define VOTINGDIALOG_WIDTH_TotalShares        100
#define VOTINGDIALOG_WIDTH_Url                150
#define VOTINGDIALOG_WIDTH_BestAnswer         80

class VotingItem {
public:
    int rowNumber_;
    QString title_;
    time_t expiration_;
    QString shareType_;
    QString question_;
    QString answers_;
    QString arrayOfAnswers_;
    QString totalParticipants_;
    QString totalShares_;
    QString url_;
    QString bestAnswer_;
};

// VotingTableModel
//
class VotingTableModel
    : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit VotingTableModel();
    ~VotingTableModel();

    enum ColumnIndex {
        RowNumber = 0,
        Title = 1,
        Expiration = 2,
        ShareType = 3,
        Question = 4,
        Answers = 5,
        TotalParticipants = 6,
        TotalShares = 7,
        Url = 8,
        BestAnswer = 9,
    };

    enum Roles {
        RowNumberRole = Qt::UserRole,
        TitleRole,
        ExpirationRole,
        ShareTypeRole,
        QuestionRole,
        AnswersRole,
        TotalParticipantsRole,
        TotalSharesRole,
        UrlRole,
        BestAnswerRole,

        SortRole,
    };

    int rowCount(const QModelIndex &) const;
    int columnCount(const QModelIndex &) const;
    QVariant data(const QModelIndex &, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    const VotingItem *index(int row) const;
    QModelIndex index(int row, int column, const QModelIndex &parent=QModelIndex()) const;
    Qt::ItemFlags flags(const QModelIndex &) const;
    void resetData(void);

private:
    QStringList columns_;
    QList<VotingItem *> data_;
};


// VotingProxyModel
//
class VotingProxyModel
    : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    explicit VotingProxyModel(QObject *parent=0);
    void setFilterTitle(const QString &);
    void setFilterQuestion(const QString &);
    void setFilterAnswers(const QString &);
    void setFilterUrl(const QString &);

protected:
    bool filterAcceptsRow(int, const QModelIndex &) const;

private:
    QString filterTitle_;
    QString filterQuestion_;
    QString filterAnswers_;
    QString filterUrl_;
};

class VotingChartDialog;
class VotingVoteDialog;
class NewPollDialog;

// VotingDialog
//
class VotingDialog
    : public QDialog
{
    Q_OBJECT

public:
    explicit VotingDialog(QWidget *parent=0);

private:
    QLineEdit *filterTitle;
    QLineEdit *filterQuestion;
    QLineEdit *filterAnswers;
    QLineEdit *filterUrl;
    QPushButton *resetButton;
    QPushButton *newPollButton;
    QTableView *tableView_;
    VotingTableModel *tableModel_;
    VotingProxyModel *proxyModel_;
    VotingChartDialog *chartDialog_;
    VotingVoteDialog *voteDialog_;
    NewPollDialog *pollDialog_;

private:
    virtual void showEvent(QShowEvent *);
    virtual void resizeEvent(QResizeEvent *);
    void tableColResize(void);
    bool eventFilter(QObject *, QEvent *);

public slots:
    void filterTitleChanged(const QString &);
    void filterQuestionChanged(const QString &);
    void filterAnswersChanged(const QString &);
    void filterUrlChanged(const QString &);
    void resetData(void);
    void showChartDialog(void);
    void showContextMenu(const QPoint &);
    void showVoteDialog(void);
    void showNewPollDialog(void);
};

// VotingChartDialog
//
class VotingChartDialog
    : public QDialog
{
    Q_OBJECT

public:
    explicit VotingChartDialog(QWidget *parent=0);
    void resetData(const VotingItem *);

private:
    QtCharts::QChart *chart_;
    QLabel *question_;
    QLabel *url_;
    QLabel *answer_;
};

// VotingVoteDialog
//
class VotingVoteDialog
    : public QDialog
{
    Q_OBJECT

public:
    explicit VotingVoteDialog(QWidget *parent=0);
    void resetData(const VotingItem *);

private:
    QLabel *question_;
    QLabel *url_;
    QLabel *answer_;
    QLabel *voteNote_;
    QListWidget *answerList_;
    QListWidgetItem *answerItem;
    QPushButton *voteButton;
    QString GetVoteValue(void);
    QString sVoteTitle;
    
private slots:
    void vote(void);
};

// NewPollDialog
//
class NewPollDialog
    : public QDialog
{
    Q_OBJECT

public:
    explicit NewPollDialog(QWidget *parent=0);

public slots:
    void resetData(void);

private:
    QLineEdit *title_;
    QLineEdit *days_;
    QLineEdit *question_;
    QLineEdit *url_;
    QComboBox *shareTypeBox_;
    QLabel *pollNote_;
    QListWidget *answerList_;
    QListWidgetItem *answerItem;
    QPushButton *addItemButton;
    QPushButton *removeItemButton;
    QPushButton *clearAllButton;
    QPushButton *pollButton;
    void GetPollValues(void);
    QString sPollTitle;
    QString sPollDays;
    QString sPollQuestion;
    QString sPollUrl;
    QString sPollShareType;
    QString sPollAnswers;

private slots:
    void createPoll(void);
    void editItem (QListWidgetItem *item);
    void addItem (void);
    void removeItem(void);
    void showContextMenu(const QPoint &);
};

#endif // VOTINGDIALOG_H
