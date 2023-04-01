#include "pch.hpp"

namespace EventTests
{
    namespace EventManagerTest
    {
        using namespace VL;

        class MockEvent : public Event
        {

        };

        TEST(EventManagerTest, TestSubscribeAndNotify)
        {
            // Given
            EventManager em;
            int count = 0;

            // When
            // Subscribe to an event
            em.subscribe(EventManager::EVENT_TYPE::APP_RENDER, [&](std::shared_ptr<Event> e) {
                count++;
            });

            // Notify the event
            em.notify(EventManager::EVENT_TYPE::APP_RENDER, std::make_shared<MockEvent>());

            // Then
            EXPECT_EQ(count, 1);
        }

        TEST(EventManagerTest, TestUnsubscribe)
        {
            // Given
            EventManager em;
            int count = 0;

            // When
            // Subscribe to an event
            auto callback = [&](std::shared_ptr<Event> e) {
                count++;
            };
            em.subscribe(EventManager::EVENT_TYPE::APP_RENDER, callback);

            // Unsubscribe from the event
            em.unsubscribe(EventManager::EVENT_TYPE::APP_RENDER, callback);

            // Notify the event
            em.notify(EventManager::EVENT_TYPE::APP_RENDER, std::make_shared<MockEvent>());

            // Then
            EXPECT_EQ(count, 0);
        }

        TEST(EventManagerTest, TestUnsubscribeNotExistingCallback)
        {
            // Given
            EventManager em;
            int count = 0;

            // When
            // Subscribe to an event
            auto callback = [&](std::shared_ptr<Event> e) {
                count++;
            };

            // Unsubscribe from the event
            em.unsubscribe(EventManager::EVENT_TYPE::APP_RENDER, callback);

            // Notify the event
            em.notify(EventManager::EVENT_TYPE::APP_RENDER, std::make_shared<MockEvent>());

            // Then
            EXPECT_EQ(count, 0);
        }
    }
}