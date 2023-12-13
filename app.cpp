#include <QApplication>
#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>

class Calculator : public QWidget {
public:
     Calculator(QWidget *parent = nullptr) : QWidget(parent) {
         // Create widgets
         display = new QLineEdit(this);
         buttons = new QGridLayout(this);

         // Set the layout for the buttons
         setLayout(buttons);

         // Set the input widget to read-only mode
         display->setReadOnly(true);

         // Set button sizes
         display->setFixedHeight(50);
         display->setFont(QFont("Arial", 18));

         // Add buttons to the layout
         for (int i = 0; i < 10; ++i) {
             QString buttonText = QString::number(i);
             QPushButton *button = createButton(buttonText);
             connect(button, SIGNAL(clicked()), this, SLOT(digitClicked()));
             buttons->addWidget(button, i / 3, i % 3);
         }

         // Reset button
         QPushButton *clearButton = createButton("C");
         connect(clearButton, SIGNAL(clicked()), this, SLOT(clear()));
         buttons->addWidget(clearButton, 3, 0);

         // Button "="
         QPushButton *equalButton = createButton("=");
         connect(equalButton, SIGNAL(clicked()), this, SLOT(equalClicked()));
         buttons->addWidget(equalButton, 3, 1);

         // Button "+"
         QPushButton *plusButton = createButton("+");
         connect(plusButton, SIGNAL(clicked()), this, SLOT(plusClicked()));
         buttons->addWidget(plusButton, 0, 3);

         // Button "-"
         QPushButton *minusButton = createButton("-");
         connect(minusButton, SIGNAL(clicked()), this, SLOT(minusClicked()));
         buttons->addWidget(minusButton, 1, 3);

         // Button "*"
         QPushButton *multiplyButton = createButton("*");
         connect(multiplyButton, SIGNAL(clicked()), this, SLOT(multiplyClicked()));
         buttons->addWidget(multiplyButton, 2, 3);

         // Button "/"
         QPushButton *divideButton = createButton("/");
         connect(divideButton, SIGNAL(clicked()), this, SLOT(divideClicked()));
         buttons->addWidget(divideButton, 3, 3);

         // Set the main layout
         setLayout(buttons);
     }

private slots:
     // Handler for buttons with numbers
     void digitClicked() {
         QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
         if (clickedButton) {
             QString digit = clickedButton->text();
             display->setText(display->text() + digit);
         }
     }

     // Handler for the "Reset" button
     void clear() {
         display->clear();
     }

     // Handler for the "=" button
     void equalClicked() {
         QString expression = display->text();
         QRegExp regExp("[+\\-*/]");
         QStringList operands = expression.split(regExp);

         if (operands.size() == 2) {
             double operand1 = operands[0].toDouble();
             double operand2 = operands[1].toDouble();
             double result = 0;

             if (expression.contains('+')) {
                 result = operand1 + operand2;
             } else if (expression.contains('-')) {
                 result = operand1 - operand2;
             } else if (expression.contains('*')) {
                 result = operand1 * operand2;
             } else if (expression.contains('/')) {
                 if (operand2 != 0) {
                     result = operand1 / operand2;
                 } else {
                     display->setText("Error");
                     return;
                 }
             }

             display->setText(QString::number(result));
         }
     }

     // Handler for arithmetic operation buttons
     void operatorClicked() {
         QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
         if (clickedButton) {
             QString op = clickedButton->text();
             display->setText(display->text() + " " + op + " ");
         }
     }

     // Handlers for arithmetic operation buttons
     void plusClicked() {
         operatorClicked();
     }

     void minusClicked() {
         operatorClicked();
     }

     void multiplyClicked() {
         operatorClicked();
     }

     void divideClicked() {
         operatorClicked();
     }

private:
     // Helper function for creating buttons
     QPushButton *createButton(const QString &text) {
         QPushButton*
