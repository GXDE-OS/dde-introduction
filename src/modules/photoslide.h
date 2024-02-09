#ifndef PHOTOSLIDE_H
#define PHOTOSLIDE_H

#include "moduleinterface.h"

#include <QGraphicsOpacityEffect>
#include <QLabel>
#include <QPropertyAnimation>
#include <QWidget>

class PhotoSlide : public ModuleInterface {
    Q_OBJECT
public:
    explicit PhotoSlide(QWidget* parent = nullptr);

    void updateBigIcon() override;
    void updateSmallIcon() override;
    void updateSelectBtnPos() override;

public slots:
    void start(bool disable_slide, bool disable_animation, int duration);
    void stop();
    void setPhotoList(const QStringList& list);

private slots:
    // Update slide image while switching to next animation loop
    void updateSlideImage();

private:
    int                      slide_index_;
    QStringList              m_photoList;
    QLabel*                  container_label_   = nullptr;
    QPropertyAnimation*      pos_animation_     = nullptr;
    QGraphicsOpacityEffect*  opacity_effect_    = nullptr;
    QPropertyAnimation*      opacity_animation_ = nullptr;
    QParallelAnimationGroup* animation_group_   = nullptr;
    QVariantAnimation*       null_animation_    = nullptr;
};

#endif  // PHOTOSLIDE_H
