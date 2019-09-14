#include <QSpinBox>
#include <QFileDialog>
#include <QTextStream>
#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_precisionTest(new PrecisionTest(ui, this))
{
    ui->setupUi(this);
    setWindowTitle(qApp->applicationName());

    ui->spinBox_minTicksInterval->setValue(DEFAULT_MIN_TICK_INTERVAL);
    ui->spinBox_maxTicksInterval->setValue(DEFAULT_MAX_TICK_INTERVAL);
    ui->spinBox_ticksIntervalStep->setValue(DEFAULT_TICK_INTERVAL_STEP);
    ui->spinBox_ticksCount->setValue(DEFAULT_TICKS_COUNT);
    ui->comboBox_type->insertItems(0, TYPE_STRINGS);

    connect(ui->pushButton_run,     &QPushButton::released, this, &MainWindow::run);
    connect(ui->pushButton_stop,    &QPushButton::released, this, &MainWindow::stop);
    connect(m_precisionTest,        &PrecisionTest::step,   this, &MainWindow::changeStep);

    connect(m_precisionTest, &PrecisionTest::done, this, [this]() {
        setWidgetsEnabled(true);
    });

    connect(ui->pushButton_save, &QPushButton::released, this, &MainWindow::save);
}



MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::run()
{
    setWidgetsEnabled(false);
    ui->textBrowser->clear();
    m_stepsCount = (ui->spinBox_maxTicksInterval->value()-ui->spinBox_minTicksInterval->value())
            /ui->spinBox_ticksIntervalStep->value()+1;
    m_currentStep = 0;
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(m_stepsCount);
    m_precisionTest->run();
}



void MainWindow::stop()
{
    m_precisionTest->stop();
    setWidgetsEnabled(true);
}



void MainWindow::changeStep(int ticksInterval, double averageFault)
{
    const QString text = QString("%1   %2").arg(ticksInterval).arg(QString::number(averageFault, 'f', 6));
    ui->textBrowser->append(text);
    ++m_currentStep;
    ui->progressBar->setValue(m_currentStep);
    const QString text2 = QString("%1 / %2").arg(m_currentStep).arg(m_stepsCount);
    ui->progressBar->setFormat(text2);
}



void MainWindow::setWidgetsEnabled(bool enabled)
{
    ui->spinBox_minTicksInterval->setEnabled(enabled);
    ui->spinBox_maxTicksInterval->setEnabled(enabled);
    ui->spinBox_ticksIntervalStep->setEnabled(enabled);
    ui->spinBox_ticksCount->setEnabled(enabled);
    ui->comboBox_type->setEnabled(enabled);
}



void MainWindow::save()
{
    QString fileName;
    fileName = QFileDialog::getSaveFileName(this, tr("Save"), "ltimer.txt", "*.txt");

    if (!fileName.isEmpty()) {
        QFile file(fileName);

        if (file.open(QIODevice::WriteOnly)) {
            QTextStream stream(&file);
            stream << ui->textBrowser->toPlainText();
            file.close();
        }
    }
}
