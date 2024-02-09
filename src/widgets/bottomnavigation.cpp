#include "bottomnavigation.h"

#include <QHBoxLayout>
#include <dimagebutton.h>
#include <QDesktopServices>
#include <QUrl>
#include <QEvent>
#include <QProcess>

DWIDGET_USE_NAMESPACE

BottomNavigation::BottomNavigation(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout;
    layout->setContentsMargins(20, 10, 20, 14);
    layout->setSpacing(10);

    DImageButton *sinaBtn = new DImageButton(":/resources/weibo.svg",
                                             ":/resources/weibo.svg",
                                             ":/resources/weibo.svg");
    DImageButton *twitterBtn = new DImageButton(":/resources/Twitter.svg",
                                                ":/resources/Twitter.svg",
                                                ":/resources/Twitter.svg");
    DImageButton *facebook = new DImageButton(":/resources/Facebook.svg",
                                              ":/resources/Facebook.svg",
                                              ":/resources/Facebook.svg");

    DImageButton *offical = new DImageButton;
    offical->setText(tr("Home Page"));

    DImageButton *community = new DImageButton;
    community->setText(tr("Community"));

    DImageButton *feedback = new DImageButton;
    feedback->setText(tr("Feedback"));

    DImageButton *help = new DImageButton;
    help->setText(tr("Help"));

#ifndef PROFESSIONAL
    DImageButton *thank = new DImageButton;
    thank->setText(tr("Acknowledgements"));
#endif

    DImageButton *mail = new DImageButton(":/resources/Mail.svg",
                                          ":/resources/Mail.svg",
                                          ":/resources/Mail.svg");

    QList<DImageButton*> list;

    list << sinaBtn << twitterBtn << facebook << offical << community << feedback << help
#ifndef PROFESSIONAL
    << thank
#endif
    << mail;

    for (DImageButton *w : list) {
        w->installEventFilter(this);
        connect(w, &DImageButton::clicked, this, &BottomNavigation::onButtonClicked);
    }

    m_buttons[sinaBtn] = "https://weibo.com/p/1006062675284423/home";
    m_buttons[twitterBtn] = "https://twitter.com/linux_deepin";
    m_buttons[facebook] = "https://www.facebook.com/deepinlinux/";

#ifndef PROFESSIONAL
    m_buttons[offical] = "https://www.deepin.org/";
#else
    m_buttons[offical] = "https://www.deepin.com/";
#endif
    m_buttons[community] = "https://bbs.deepin.org/";
    m_buttons[feedback] = "http://feedback.deepin.org/";
#ifndef PROFESSIONAL
    m_buttons[thank] = "https://www.deepin.org/acknowledgments/deepin/";
#endif
    m_buttons[mail] = "mailto:support@deepin.com";

    connect(help, &DImageButton::clicked, this, [=] {
        QProcess::startDetached("/usr/bin/dman");
    });

    layout->addWidget(sinaBtn, 0, Qt::AlignCenter);
    layout->addWidget(twitterBtn, 0, Qt::AlignCenter);
    layout->addWidget(facebook, 0, Qt::AlignCenter);
    layout->addStretch();
    layout->addWidget(offical, 0, Qt::AlignCenter);
    layout->addWidget(community, 0, Qt::AlignCenter);
    layout->addWidget(feedback, 0, Qt::AlignCenter);
    layout->addWidget(help, 0, Qt::AlignCenter);
#ifndef PROFESSIONAL
    layout->addWidget(thank, 0, Qt::AlignCenter);
#endif
    layout->addStretch();
    layout->addWidget(mail, 0, Qt::AlignCenter);

    setLayout(layout);

    setStyleSheet("QLabel {"
                  "color: #0082FA;"
                  "}");
}

void BottomNavigation::onButtonClicked()
{
    DImageButton *button = qobject_cast<DImageButton*>(sender());

    Q_ASSERT(button);

    QDesktopServices::openUrl(QUrl(m_buttons[button]));
}

bool BottomNavigation::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::Enter) {
        setCursor(Qt::PointingHandCursor);
    }

    if (event->type() == QEvent::Leave) {
        setCursor(Qt::ArrowCursor);
    }

    return QWidget::eventFilter(watched, event);
}
