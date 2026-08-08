#include <Geode/Geode.hpp>
#include <Geode/modify/EditorUI.hpp>

using namespace geode::prelude;

class $modify(MyEditorUI, EditorUI) {
    CCSprite* m_phoneCursor = nullptr;

    bool init(LevelEditorLayer* layer) {
        if (!EditorUI::init(layer)) return false;

        // --- ДЛЯ ПК (WINDOWS): Скрываем хвост курсора ---
        #ifdef GEODE_IS_WINDOWS
        if (this->m_swipeParticles) {
            this->m_swipeParticles->setVisible(false);
            this->m_swipeParticles->setScale(0.0f);
        }
        #endif

        // --- ДЛЯ ТЕЛЕФОНА (ANDROID): Создаем круглый курсор ---
        #ifdef GEODE_IS_ANDROID
        auto cursor = CCSprite::createWithSpriteFrameName("gj_commentSide_001.png");
        if (cursor) {
            cursor->setScale(1.2f);
            cursor->setOpacity(180);
            this->addChild(cursor, 100);
            m_fields->m_phoneCursor = cursor;
        }
        #endif

        return true;
    }

    void ccTouchMoved(CCTouch* touch, CCEvent* event) {
        EditorUI::ccTouchMoved(touch, event);

        #ifdef GEODE_IS_ANDROID
        if (m_fields->m_phoneCursor) {
            CCPoint touchLocation = touch->getLocation();
            m_fields->m_phoneCursor->setPosition(touchLocation);
        }
        #endif
    }
};
