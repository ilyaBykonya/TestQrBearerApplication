#include "TokenView.h"
#include "QrCode/QrCodeDialog.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QStringListModel>

TokenView::TokenView(QWidget* parent)
    :QWidget{ parent },
     m_tokens{ new TokenModel{} },
     m_view{ new QListView{} } {
        m_view->setModel(m_tokens);
        auto showTokenButton = new QPushButton{ "*" };
        auto refreshModelButton = new QPushButton{ "U" };
        auto createTokenButton = new QPushButton{ "+" };
        auto removeTokenButton = new QPushButton{ "-" };

        connect(m_view, &QAbstractItemView::doubleClicked, this, &TokenView::showToken);
        connect(showTokenButton, &QPushButton::clicked, this, &TokenView::showToken);
        connect(refreshModelButton, &QPushButton::clicked, m_tokens, &TokenModel::refresh);
        connect(createTokenButton, &QPushButton::clicked, this, &TokenView::createToken);
        connect(removeTokenButton, &QPushButton::clicked, this, &TokenView::removeToken);

        auto layout = new QVBoxLayout{};
            auto buttonLayout = new QHBoxLayout{};
            buttonLayout->addWidget(createTokenButton);
            buttonLayout->addWidget(removeTokenButton);
            buttonLayout->addWidget(showTokenButton);
            buttonLayout->addStretch(1);
        layout->addLayout(buttonLayout, 0);
        layout->addWidget(m_view, 1);
        this->setLayout(layout);
        m_tokens->refresh();
    }

void TokenView::showToken() {
    const auto selection = m_view->selectionModel()->selection();
    if(selection.size() != 1)
        return;

    const auto token = m_tokens->tokenAt(selection.indexes().front().row());
    QrCodeDialog qrCoreView{ token.first.toRfc4122(), this };
    qrCoreView.showMaximized();
    qrCoreView.exec();
}
void TokenView::createToken() {
    bool isValidExpirationSpan{};
    const auto expirationSpan = QInputDialog::getInt(this, "Expiration span", "Seconds:", 86400,
        0, std::numeric_limits<qint32>::max(), 1, &isValidExpirationSpan);
    if(not isValidExpirationSpan)
        return;

    m_tokens->create(expirationSpan);
}
void TokenView::removeToken() {
    const auto selection = m_view->selectionModel()->selection();
    if(selection.size() != 1)
        return;

    const auto token = m_tokens->tokenAt(selection.indexes().front().row());
    m_tokens->remove(token.first);
}


