#include "rankingform.h"

#include "RankingManager.h"

#include <QHeaderView>
#include <QLabel>
#include <QPushButton>
#include <QTabWidget>
#include <QTableWidget>
#include <QVBoxLayout>

#include <algorithm>

bool compareScores(const ScoreEntry &left, const ScoreEntry &right)
{
    if (left.difficulty != right.difficulty)
        return static_cast<int>(left.difficulty) < static_cast<int>(right.difficulty);

    if (left.timeMs != right.timeMs)
        return left.timeMs < right.timeMs;

    return left.username.toLower() < right.username.toLower();
}

bool compareScoresByTime(const ScoreEntry &left, const ScoreEntry &right)
{
    if (left.timeMs != right.timeMs)
        return left.timeMs < right.timeMs;

    return left.username.toLower() < right.username.toLower();
}

RankingForm::RankingForm(QWidget *parent)
    : QDialog(parent)
{
    setupUi();
}

RankingForm::~RankingForm()
{
}

void RankingForm::setupUi()
{
    RankingManager rankingManager;
    std::vector<ScoreEntry> allScores = rankingManager.loadScores();

    setWindowTitle("Rankings");
    setModal(true);
    setFixedSize(700, 470);

    setStyleSheet(
        "QDialog { background-color: #08111f; }"

        "QLabel { color: #d9e7ff; }"

        "QTabWidget::pane { border: 1px solid #273247; }"

        "QTabBar::tab {"
        "    background-color: #111a2b;"
        "    color: #d9e7ff;"
        "    padding: 8px 14px;"
        "    border: 1px solid #273247;"
        "}"

        "QTabBar::tab:selected {"
        "    background-color: #1a2433;"
        "}"

        "QPushButton {"
        "    background-color: #1a2433;"
        "    color: #e5ecf6;"
        "    border: 1px solid #273247;"
        "    padding: 6px 18px;"
        "}"

        "QPushButton:hover { background-color: #223047; }"
        );

    QVBoxLayout *layout = new QVBoxLayout(this);
    QLabel *titleLabel = new QLabel("Mejores tiempos", this);

    QLabel *totalScoresLabel = new QLabel(
        allScores.empty() ? "Todavia no se han guardado victorias. Gana una partida para aparecer aqui."
        : QString("Total de puntajes guardados: %1").arg(allScores.size()),
        this);

    QTabWidget *tabs = new QTabWidget(this);
    QPushButton *closeButton = new QPushButton("Cerrar", this);

    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(18);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    titleLabel->setAlignment(Qt::AlignCenter);

    totalScoresLabel->setAlignment(Qt::AlignCenter);

    for (Difficulty difficulty : {Difficulty::BEGINNER, Difficulty::INTERMEDIATE, Difficulty::EXPERT}) {

        std::vector<ScoreEntry> scores = rankingManager.loadScoresDifficulty(difficulty);

        std::sort(scores.begin(), scores.end(), compareScoresByTime);

        if (scores.size() > 10)
            scores.resize(10);

        tabs->addTab(buildRankingTable(scores, tabs), difficultyToText(difficulty));
    }

    connect(closeButton, &QPushButton::clicked, this, &QDialog::accept);

    layout->addWidget(titleLabel);
    layout->addWidget(totalScoresLabel);
    layout->addWidget(tabs);
    layout->addWidget(closeButton, 0, Qt::AlignCenter);
}

QString RankingForm::difficultyToText(Difficulty difficulty) const
{
    switch (difficulty) {
    case Difficulty::BEGINNER:
        return "Beginner";
    case Difficulty::INTERMEDIATE:
        return "Intermediate";
    case Difficulty::EXPERT:
        return "Expert";
    }

    return "Unknown";
}

QString RankingForm::formatTime(qint64 timeMs) const
{
    const qint64 totalSeconds = timeMs / 1000;
    const qint64 minutes = totalSeconds / 60;
    const qint64 seconds = totalSeconds % 60;
    const qint64 centiseconds = (timeMs % 1000) / 10;

    return QString("%1:%2.%3").arg(minutes, 2, 10, QChar('0'))
        .arg(seconds, 2, 10, QChar('0')).arg(centiseconds, 2, 10, QChar('0'));
}

QWidget *RankingForm::buildRankingTable(const std::vector<ScoreEntry> &scores, QWidget *parent)
{
    QWidget *container = new QWidget(parent);
    QVBoxLayout *layout = new QVBoxLayout(container);
    layout->setContentsMargins(0, 0, 0, 0);

    if (scores.empty()) {
        QLabel *emptyLabel = new QLabel("Todavia no hay puntajes registrados para esta dificultad.", container);
        emptyLabel->setAlignment(Qt::AlignCenter);
        emptyLabel->setStyleSheet("color: #d9e7ff; font-size: 15px;");
        layout->addWidget(emptyLabel);
        return container;
    }

    QTableWidget *table = new QTableWidget(container);
    table->setColumnCount(3);
    table->setHorizontalHeaderLabels({"Posicion", "Jugador", "Tiempo"});
    table->setRowCount(static_cast<int>(scores.size()));
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSelectionMode(QAbstractItemView::NoSelection);
    table->verticalHeader()->setVisible(false);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->horizontalHeader()->setHighlightSections(false);
    table->setAlternatingRowColors(false);
    table->setStyleSheet(
        "QTableWidget {"
        "    background-color: #0f1724;"
        "    color: #e5ecf6;"
        "    gridline-color: #273247;"
        "    border: 1px solid #273247;"
        "}"
        "QHeaderView::section {"
        "    background-color: #5b21b6;"
        "    color: white;"
        "    padding: 4px;"
        "    border: 1px solid #273247;"
        "}"
        "QTableWidget::item {"
        "    padding: 4px;"
        "}"
        );

    for (size_t i = 0; i < scores.size(); ++i) {
        const ScoreEntry &score = scores[i];

        table->setItem(i, 0, new QTableWidgetItem(QString::number(i + 1)));
        table->setItem(i, 1, new QTableWidgetItem(score.username));
        table->setItem(i, 2, new QTableWidgetItem(formatTime(score.timeMs)));
    }

    layout->addWidget(table);
    return container;
}
