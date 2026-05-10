#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    auto db = std::make_shared<Connections>();
    auto threadsService = std::make_shared<ThreadRepository>(db);
    auto threadController = std::make_shared<ThreadController>(threadsService);

    TEST_CLASS(UnitTest1)
    {
    public:
        TEST_METHOD(TestCreateThread_Succeeds)
        {
            db->connectDataBase();
            Logger::WriteMessage(L"=== Начало теста: создать ветку (успех) ===");

            try {
                auto& conn = db->getConnection();
                Logger::WriteMessage(L" Подключение к БД установлено");
            }
            catch (const std::exception& e) {
                std::string msg = " Ошибка подключения: ";
                msg += e.what();
                Logger::WriteMessage(std::wstring(msg.begin(), msg.end()).c_str());
                Assert::Fail(L"Нет подключения к БД");
            }

            std::string id = "bf26081e-c8df-403b-a555-609157edb1b4";
            bool created = threadController->createThread("Tests1", 32, id);
            Logger::WriteMessage(created ? L" Ветка создана" : L" Ветка НЕ создана");
            Assert::IsTrue(created, L"Ожидалось успешное создание ветки");

            // cleanup
            if (created)
            {
                bool deleted = threadController->deleteThread(id);
                Logger::WriteMessage(deleted ? L"Ветка удалена (cleanup)" : L"Ветка НЕ удалена (cleanup)");
            }
        }

        TEST_METHOD(TestCreateThread_Fails_EmptyTitle)
        {
            db->connectDataBase();
            Logger::WriteMessage(L"=== Начало теста: создать ветку (пустое название) ===");

            try {
                auto& conn = db->getConnection();
                Logger::WriteMessage(L" Подключение к БД установлено");
            }
            catch (const std::exception& e) {
                std::string msg = " Ошибка подключения: ";
                msg += e.what();
                Logger::WriteMessage(std::wstring(msg.begin(), msg.end()).c_str());
                Assert::Fail(L"Нет подключения к БД");
            }

            std::string id = "bf55010e-d8df-403b-a555-609157edb1b4";
            bool created = threadController->createThread("", 32, id);
            Logger::WriteMessage(created ? L" Ветка создана (unexpected)" : L" Ветка НЕ создана (expected)");
            Assert::IsFalse(created, L"Ожидалось, что создание с пустым названием не будет успешным");

            // cleanup if unexpectedly created
            if (created)
            {
                threadController->deleteThread(id);
            }
        }

        TEST_METHOD(TestDeleteThread_CreateThenDelete)
        {
            db->connectDataBase();
            Logger::WriteMessage(L"=== Начало теста: создать и удалить ветку ===");

            try {
                auto& conn = db->getConnection();
                Logger::WriteMessage(L" Подключение к БД установлено");
            }
            catch (const std::exception& e) {
                std::string msg = " Ошибка подключения: ";
                msg += e.what();
                Logger::WriteMessage(std::wstring(msg.begin(), msg.end()).c_str());
                Assert::Fail(L"Нет подключения к БД");
            }

            std::string id = "bf26010e-c8df-403b-a555-609157edb1b4";
            bool created = threadController->createThread("TempTestForDelete", 32, id);
            Logger::WriteMessage(created ? L" Ветка создана для удаления" : L" Ветка возможно уже существовала");

            bool deleted = threadController->deleteThread(id);
            Logger::WriteMessage(deleted ? L"Ветка удалена" : L"Ветка НЕ удалена");
            Assert::IsTrue(deleted, L"Ожидалось успешное удаление ветки");
        }

        TEST_METHOD(TestDeleteThread_Fails_EmptyId)
        {
            db->connectDataBase();
            Logger::WriteMessage(L"=== Начало теста: удалить ветку с пустым id ===");

            try {
                auto& conn = db->getConnection();
                Logger::WriteMessage(L" Подключение к БД установлено");
            }
            catch (const std::exception& e) {
                std::string msg = " Ошибка подключения: ";
                msg += e.what();
                Logger::WriteMessage(std::wstring(msg.begin(), msg.end()).c_str());
                Assert::Fail(L"Нет подключения к БД");
            }

            std::string id = "";
            bool deleted = threadController->deleteThread(id);
            Logger::WriteMessage(deleted ? L"Ветка удалена (unexpected)" : L"Ветка НЕ удалена (expected)");
            Assert::IsFalse(deleted, L"Ожидалось, что удаление с пустым id не выполнится");
        }

        // --- Tests for updateThread ---

        TEST_METHOD(TestUpdateThread_Succeeds)
        {
            db->connectDataBase();
            Logger::WriteMessage(L"=== Начало теста обновления названия ветки (успех) ===");
            try {
                auto& conn = db->getConnection();
                Logger::WriteMessage(L" Подключение к БД установлено");
            }
            catch (const std::exception& e) {
                std::string msg = " Ошибка подключения: ";
                msg += e.what();
                Logger::WriteMessage(std::wstring(msg.begin(), msg.end()).c_str());
                Assert::Fail(L"Нет подключения к БД");
            }

            std::string id = "bf26012e-c8df-403b-a555-609157edb1b4";

            bool created = threadController->createThread("OldTitle", 32, id);
            Logger::WriteMessage(created ? L" Ветка создана для теста обновления" : L" Ветка уже могла существовать");

            bool updated = threadController->updateTitleThread(id, "NewTitle");
            Logger::WriteMessage(updated ? L"Название обновлено" : L"Название НЕ обновлено");
            Assert::IsTrue(updated, L"Ожидалось успешное обновление названия");

            bool deleted = threadController->deleteThread(id);
            Logger::WriteMessage(deleted ? L"Ветка удалена (cleanup)" : L"Ветка НЕ удалена (cleanup)");
        }

        TEST_METHOD(TestUpdateThread_Fails_EmptyTitle)
        {
            db->connectDataBase();
            Logger::WriteMessage(L"=== Начало теста обновления названия ветки (пустое название) ===");
            try {
                auto& conn = db->getConnection();
                Logger::WriteMessage(L" Подключение к БД установлено");
            }
            catch (const std::exception& e) {
                std::string msg = " Ошибка подключения: ";
                msg += e.what();
                Logger::WriteMessage(std::wstring(msg.begin(), msg.end()).c_str());
                Assert::Fail(L"Нет подключения к БД");
            }

            std::string id = "bf26013e-c8df-403b-a555-609157edb1b4";

            bool created = threadController->createThread("TitleBefore", 32, id);
            Logger::WriteMessage(created ? L" Ветка создана для теста (empty title)" : L" Ветка уже могла существовать");

            bool updated = threadController->updateTitleThread(id, "");
            Logger::WriteMessage(updated ? L"Название обновлено (unexpected)" : L"Название НЕ обновлено (expected)");
            Assert::IsFalse(updated, L"Ожидалось, что обновление с пустым названием не выполнится");

            bool deleted = threadController->deleteThread(id);
            Logger::WriteMessage(deleted ? L"Ветка удалена (cleanup)" : L"Ветка НЕ удалена (cleanup)");
        }

        TEST_METHOD(TestUpdateThread_Fails_NonexistentId)
        {
            db->connectDataBase();
            Logger::WriteMessage(L"=== Начало теста обновления названия ветки (несуществующий id) ===");
            try {
                auto& conn = db->getConnection();
                Logger::WriteMessage(L" Подключение к БД установлено");
            }
            catch (const std::exception& e) {
                std::string msg = " Ошибка подключения: ";
                msg += e.what();
                Logger::WriteMessage(std::wstring(msg.begin(), msg.end()).c_str());
                Assert::Fail(L"Нет подключения к БД");
            }

            std::string id = "00000000-0000-0000-0000-000000000000";

            bool updated = threadController->updateTitleThread(id, "DoesNotMatter");
            Logger::WriteMessage(updated ? L"Название обновлено (unexpected)" : L"Название НЕ обновлено (expected)");
            Assert::IsFalse(updated, L"Ожидалось, что обновление для несуществующего id не выполнится");
        }
    };
}