#include <gtest/gtest.h>
#include "../task1/Menu/CMenu.h"
#include "../task1/Document/CDocument.h"

TEST(MenuTest, AddItemAndShowInstructions)
{
    CMenu menu;
    menu.AddItem("First", "First command", [](std::istringstream&) {
    });
    menu.AddItem("Second", "Second command", [](std::istringstream&) {
    });

    std::stringstream output;
    std::streambuf* oldCoutBuffer = std::cout.rdbuf(output.rdbuf());

    menu.ShowInstructions();
    std::cout.rdbuf(oldCoutBuffer);

    std::string expectedInstructions = "Commands list:\n  First. First command\n  Second. Second command\n";
    EXPECT_EQ(output.str(), expectedInstructions);
}

TEST(MenuTest, ExecuteCommand)
{
    CMenu menu;
    bool commandExecuted = false;

    menu.AddItem("Test", "Test command", [&](std::istringstream&) {
        commandExecuted = true;
    });

    std::stringstream input("Test\n"), output;
    std::streambuf* oldCinBuffer = std::cin.rdbuf(input.rdbuf());
    std::streambuf* oldCoutBuffer = std::cout.rdbuf(output.rdbuf());

    menu.Run();

    std::cin.rdbuf(oldCinBuffer);
    std::cout.rdbuf(oldCoutBuffer);

    EXPECT_TRUE(commandExecuted);
}

TEST(MenuTest, ExitMenu)
{
    CMenu menu;
    menu.AddItem("Exit", "Exit menu", [&](std::istringstream&) {
        menu.Exit();
    });

    std::stringstream input("Exit\n"), output;
    std::streambuf* oldCinBuffer = std::cin.rdbuf(input.rdbuf());
    std::streambuf* oldCoutBuffer = std::cout.rdbuf(output.rdbuf());

    menu.Run();

    std::cin.rdbuf(oldCinBuffer);
    std::cout.rdbuf(oldCoutBuffer);

    EXPECT_EQ(output.str().find("Commands list"), 0);
}

TEST(MenuTest, UnknownCommand)
{
    CMenu menu;
    menu.AddItem("Test", "Test command", [](std::istringstream&) {
    });

    std::stringstream input("unknown\n"), output;
    std::streambuf* oldCinBuffer = std::cin.rdbuf(input.rdbuf());
    std::streambuf* oldCoutBuffer = std::cout.rdbuf(output.rdbuf());

    menu.Run();

    std::cin.rdbuf(oldCinBuffer);
    std::cout.rdbuf(oldCoutBuffer);

    EXPECT_NE(output.str().find("Unknown command"), std::string::npos);
}

TEST(MenuTest, CommandWithArguments)
{
    CMenu menu;
    int capturedValue = 0;

    menu.AddItem("Set", "Set value", [&](std::istringstream& iss) {
        int value;
        iss >> value;
        capturedValue = value;
    });

    std::stringstream input("Set 42\n"), output;
    std::streambuf* oldCinBuffer = std::cin.rdbuf(input.rdbuf());
    std::streambuf* oldCoutBuffer = std::cout.rdbuf(output.rdbuf());

    menu.Run();

    std::cin.rdbuf(oldCinBuffer);
    std::cout.rdbuf(oldCoutBuffer);

    EXPECT_EQ(capturedValue, 42);
}

const std::string IMAGE_PATH = "img.png";

TEST(DocumentTest, InsertParagraph)
{
    CDocument document;
    EXPECT_EQ(document.GetItemsCount(), 0);

    document.InsertParagraph("First paragraph", std::nullopt);
    EXPECT_EQ(document.GetItemsCount(), 1);
    EXPECT_EQ(document.GetItem(0).GetParagraph()->GetText(), "First paragraph");

    document.InsertParagraph("Second paragraph", std::nullopt);
    EXPECT_EQ(document.GetItemsCount(), 2);
    EXPECT_EQ(document.GetItem(1).GetParagraph()->GetText(), "Second paragraph");
}

TEST(DocumentTest, ReplaceText)
{
    CDocument document;
    document.InsertParagraph("Old text", std::nullopt);
    EXPECT_EQ(document.GetItem(0).GetParagraph()->GetText(), "Old text");

    document.ReplaceText("New text", 0);
    EXPECT_EQ(document.GetItem(0).GetParagraph()->GetText(), "New text");
}

TEST(DocumentTest, InsertImage)
{
    CDocument document;
    EXPECT_EQ(document.GetItemsCount(), 0);

    document.InsertImage(IMAGE_PATH, 800, 600, std::nullopt);

    EXPECT_EQ(document.GetItemsCount(), 1);
    EXPECT_EQ(document.GetItem(0).GetImage()->GetWidth(), 800);
    EXPECT_EQ(document.GetItem(0).GetImage()->GetHeight(), 600);
}

TEST(DocumentTest, ResizeImage)
{
    CDocument document;
    document.InsertImage(IMAGE_PATH, 800, 600, std::nullopt);

    EXPECT_EQ(document.GetItem(0).GetImage()->GetWidth(), 800);
    EXPECT_EQ(document.GetItem(0).GetImage()->GetHeight(), 600);

    document.ResizeImage(0, 1024, 768);
    EXPECT_EQ(document.GetItem(0).GetImage()->GetWidth(), 1024);
    EXPECT_EQ(document.GetItem(0).GetImage()->GetHeight(), 768);
}

TEST(DocumentTest, DeleteItem)
{
    CDocument document;
    document.InsertParagraph("Paragraph 1", std::nullopt);
    document.InsertParagraph("Paragraph 2", std::nullopt);

    EXPECT_EQ(document.GetItemsCount(), 2);
    document.DeleteItem(0);
    EXPECT_EQ(document.GetItemsCount(), 1);
    EXPECT_EQ(document.GetItem(0).GetParagraph()->GetText(), "Paragraph 2");
}

TEST(DocumentTest, SetTitle)
{
    CDocument document;
    EXPECT_EQ(document.GetTitle(), "");

    document.SetTitle("New Title");
    EXPECT_EQ(document.GetTitle(), "New Title");

    document.SetTitle("Updated Title");
    EXPECT_EQ(document.GetTitle(), "Updated Title");
}

TEST(DocumentTest, UndoRedo)
{
    CDocument document;
    document.InsertParagraph("First paragraph", std::nullopt);
    document.InsertParagraph("Second paragraph", std::nullopt);

    EXPECT_TRUE(document.CanUndo());
    document.Undo();
    EXPECT_EQ(document.GetItemsCount(), 1);
    EXPECT_EQ(document.GetItem(0).GetParagraph()->GetText(), "First paragraph");

    EXPECT_TRUE(document.CanRedo());
    document.Redo();
    EXPECT_EQ(document.GetItemsCount(), 2);
    EXPECT_EQ(document.GetItem(1).GetParagraph()->GetText(), "Second paragraph");
}

std::string title = "Original Title";
std::string newTitle = "New Title";

std::unique_ptr<ICommand> CreateNewCommand()
{
    return std::move(std::make_unique<SetTitleCommand>(title, newTitle));
}

TEST(HistoryTest, InitialState)
{
    History history;
    EXPECT_FALSE(history.CanUndo());
    EXPECT_FALSE(history.CanRedo());
}

TEST(HistoryTest, AddCommandAndUndo)
{
    History history;
    history.AddAndExecuteCommand(std::move(CreateNewCommand()));

    EXPECT_TRUE(history.CanUndo());
    EXPECT_FALSE(history.CanRedo());

    history.Undo();
    EXPECT_FALSE(history.CanUndo());
    EXPECT_TRUE(history.CanRedo());
}

TEST(HistoryTest, UndoAndRedo)
{
    History history;
    history.AddAndExecuteCommand(CreateNewCommand());

    history.Undo();
    EXPECT_FALSE(history.CanUndo());
    EXPECT_TRUE(history.CanRedo());

    history.Redo();
    EXPECT_TRUE(history.CanUndo());
    EXPECT_FALSE(history.CanRedo());
}

TEST(HistoryTest, OverflowCommands)
{
    History history;
    for (int i = 0; i < 11; ++i)
    {
        history.AddAndExecuteCommand(CreateNewCommand());
    }

    EXPECT_FALSE(history.CanRedo());

    for (int i = 0; i < 10; ++i)
    {
        EXPECT_TRUE(history.CanUndo());
        history.Undo();
        EXPECT_TRUE(history.CanRedo());
    }

    EXPECT_FALSE(history.CanUndo());
}

TEST(DeleteItemCommandTest, DoExecuteDeleteItemAtSpecifiedPositionSuccess)
{
    std::vector<CDocumentItem> items;
    std::string text1 = "Paragraph 1";
    std::string text2 = "Paragraph 2";
    items.emplace_back(std::make_shared<CParagraph>(text1));
    items.emplace_back(std::make_shared<CParagraph>(text2));

    size_t position = 1;
    DeleteItemCommand command(position, items);

    command.DoExecute();

    ASSERT_EQ(items.size(), 1);
    EXPECT_EQ(items[0].GetParagraph()->GetText(), "Paragraph 1");

    command.DoUnexecute();

    ASSERT_EQ(items.size(), 2);
    EXPECT_EQ(items[1].GetParagraph()->GetText(), "Paragraph 2");
}

TEST(DeleteItemCommandTest, DoExecuteDeleteItemWithInvalidPositionError)
{
    std::vector<CDocumentItem> items;
    std::string text = "Paragraph 1";
    items.emplace_back(std::make_shared<CParagraph>(text));

    size_t invalidPosition = 5;
    DeleteItemCommand command(invalidPosition, items);

    EXPECT_THROW(command.DoExecute(), std::invalid_argument);
}

TEST(DeleteItemCommandTest, DoExecuteDeleteOnlyItemSuccess)
{
    std::vector<CDocumentItem> items;
    std::string text = "Only paragraph";
    items.emplace_back(std::make_shared<CParagraph>(text));

    size_t position = 0;
    DeleteItemCommand command(position, items);

    command.DoExecute();

    EXPECT_TRUE(items.empty());

    command.DoUnexecute();

    ASSERT_EQ(items.size(), 1);
    EXPECT_EQ(items[0].GetParagraph()->GetText(), "Only paragraph");
}


TEST(DeleteItemCommandTest, DoExecuteDeleteItemAtPositionZeroSuccess)
{
    std::vector<CDocumentItem> items;
    std::string text1 = "Paragraph 1";
    std::string text2 = "Paragraph 2";
    std::string text3 = "Paragraph 3";
    items.emplace_back(std::make_shared<CParagraph>(text1));
    items.emplace_back(std::make_shared<CParagraph>(text2));
    items.emplace_back(std::make_shared<CParagraph>(text3));

    size_t position = 0;
    DeleteItemCommand command(position, items);

    command.DoExecute();

    ASSERT_EQ(items.size(), 2);
    EXPECT_EQ(items[0].GetParagraph()->GetText(), "Paragraph 2");

    command.DoUnexecute();

    ASSERT_EQ(items.size(), 3);
    EXPECT_EQ(items[0].GetParagraph()->GetText(), "Paragraph 1");
}

TEST(DeleteItemCommandTest, DoUnexecuteOnEmptyListError)
{
    std::vector<CDocumentItem> items;

    size_t position = 0;
    DeleteItemCommand command(position, items);

    EXPECT_NO_THROW(command.DoUnexecute());

    EXPECT_TRUE(items.empty());
}

TEST(ReplaceTextCommandTest, DoExecuteReplaceTextAtPositionSuccess)
{
    std::vector<CDocumentItem> items;
    std::string oldText = "Original text";
    items.emplace_back(std::make_shared<CParagraph>(oldText));

    std::string newText = "Replaced text";
    size_t position = 0;

    ReplaceTextCommand command(newText, position, items);

    command.DoExecute();

    auto paragraph = std::dynamic_pointer_cast<CParagraph>(items[position].GetParagraph());
    ASSERT_NE(paragraph, nullptr);
    EXPECT_EQ(paragraph->GetText(), newText);

    command.DoUnexecute();

    EXPECT_EQ(paragraph->GetText(), "Original text");
}

TEST(ReplaceTextCommandTest, DoExecuteReplaceTextWithInvalidPositionError)
{
    std::vector<CDocumentItem> items;
    std::string newText = "Text for invalid position";
    size_t invalidPosition = 10;

    ReplaceTextCommand command(newText, invalidPosition, items);

    EXPECT_THROW(command.DoExecute(), std::invalid_argument);
}

TEST(ReplaceTextCommandTest, DoUnexecuteRestoreOriginalTextSuccess)
{
    std::vector<CDocumentItem> documentItems;
    std::string oldText = "Initial text";
    documentItems.emplace_back(std::make_shared<CParagraph>(oldText));

    std::string newText = "New text";
    size_t position = 0;

    ReplaceTextCommand command(newText, position, documentItems);

    command.DoExecute();

    auto paragraph = std::dynamic_pointer_cast<CParagraph>(documentItems[position].GetParagraph());
    ASSERT_NE(paragraph, nullptr);
    EXPECT_EQ(paragraph->GetText(), newText);

    command.DoUnexecute();

    EXPECT_EQ(paragraph->GetText(), "Initial text");
}

TEST(SetTitleCommandTest, DoExecuteSetsNewTitleSuccess)
{
    std::string title = "Original Title";
    std::string newTitle = "New Title";

    SetTitleCommand command(title, newTitle);

    command.DoExecute();

    EXPECT_EQ(title, "New Title");

    command.DoUnexecute();

    EXPECT_EQ(title, "Original Title");
}

TEST(SetTitleCommandTest, DoUnexecuteRevertsToOldTitleSuccess)
{
    std::string title = "Initial Title";
    std::string newTitle = "Updated Title";

    SetTitleCommand command(title, newTitle);

    command.DoExecute();

    EXPECT_EQ(title, "Updated Title");

    command.DoUnexecute();

    EXPECT_EQ(title, "Initial Title");
}

TEST(SetTitleCommandTest, RepeatedExecuteAndUnexecuteSuccess)
{
    std::string title = "Start Title";
    std::string newTitle = "Changed Title";

    SetTitleCommand command(title, newTitle);

    command.DoExecute();
    EXPECT_EQ(title, "Changed Title");

    command.DoUnexecute();
    EXPECT_EQ(title, "Start Title");

    command.DoExecute();
    EXPECT_EQ(title, "Changed Title");

    command.DoUnexecute();
    EXPECT_EQ(title, "Start Title");
}

TEST(SetTitleCommandTest, DoExecuteWithSameTitleSuccess)
{
    std::string title = "Same Title";

    SetTitleCommand command(title, title);

    command.DoExecute();

    EXPECT_EQ(title, "Same Title");

    command.DoUnexecute();

    EXPECT_EQ(title, "Same Title");
}

TEST(ResizeImageCommandTests, ExecuteResizesImageSuccess)
{
    std::vector<CDocumentItem> items;
    auto image = std::make_shared<CImage>(IMAGE_PATH, 100, 200);
    items.emplace_back(image);

    ResizeImageCommand command(0, 150, 300, items);

    EXPECT_NO_THROW(command.DoExecute());

    ASSERT_EQ(image->GetHeight(), 300);
    ASSERT_EQ(image->GetWidth(), 150);
}

TEST(ResizeImageCommandTests, ExecuteThrowsOnInvalidPositionError)
{
    std::vector<CDocumentItem> items;
    auto image = std::make_shared<CImage>(IMAGE_PATH, 100, 200);
    items.emplace_back(image);

    ResizeImageCommand command(1, 300, 150, items);

    EXPECT_THROW(command.DoExecute(), std::invalid_argument);
}

TEST(ResizeImageCommandTests, ExecuteThrowsWhenNoImageAtPositionError)
{
    std::vector<CDocumentItem> items;

    ResizeImageCommand command(0, 150, 300, items);

    EXPECT_THROW(command.DoExecute(), std::invalid_argument);
}

TEST(ResizeImageCommandTests, UnexecuteResizesBackToOriginalSizeSuccess)
{
    std::vector<CDocumentItem> items;
    auto image = std::make_shared<CImage>(IMAGE_PATH, 100, 200);
    items.emplace_back(image);

    ResizeImageCommand command(0, 150, 300, items);

    command.DoExecute();
    ASSERT_EQ(image->GetWidth(), 150);
    ASSERT_EQ(image->GetHeight(), 300);

    command.DoUnexecute();

    ASSERT_EQ(image->GetWidth(), 100);
    ASSERT_EQ(image->GetHeight(), 200);
}

TEST(ResizeImageCommandTests, UnexecuteThrowsOnInvalidPositionError)
{
    std::vector<CDocumentItem> items;
    auto image = std::make_shared<CImage>(IMAGE_PATH, 100, 200);
    items.emplace_back(image);

    ResizeImageCommand command(1, 150, 300, items);

    EXPECT_THROW(command.DoUnexecute(), std::invalid_argument);
}

bool AssertDirectoryIsNotEmpty(const std::string& path)
{
    std::filesystem::path dirPath(path);
    if (!exists(dirPath) || !is_directory(dirPath))
    {
        return false;
    }

    return std::any_of(std::filesystem::directory_iterator(dirPath), std::filesystem::directory_iterator{},
            [](const std::filesystem::directory_entry&) {
                return true;
            });
}

std::string GetFirstFileOnDirectory(const std::string& path)
{
    std::filesystem::path dirPath(path);
    if (!exists(dirPath) || !is_directory(dirPath))
    {
        return "";
    }

    for (const auto& entry : std::filesystem::directory_iterator(dirPath))
    {
        if (is_regular_file(entry.status()))
        {
            return entry.path().filename().string();
        }
    }

    return "";
}

bool AssertFilesAreEqual(const std::string& path1, const std::string& path2)
{
    std::ifstream file1(path1, std::ios::binary);
    std::ifstream file2(path2, std::ios::binary);

    if (!file1.is_open() || !file2.is_open())
    {
        return false;
    }

    file1.seekg(0, std::ios::end);
    file2.seekg(0, std::ios::end);

    if (file1.tellg() != file2.tellg())
    {
        return false;
    }

    file1.seekg(0);
    file2.seekg(0);

    return std::equal(std::istreambuf_iterator(file1),
            std::istreambuf_iterator<char>(),
            std::istreambuf_iterator(file2));
}

TEST(InsertImageCommandTests, ExecuteInsertsImageAtEndSuccess)
{
    std::vector<CDocumentItem> items;
    std::string imagePath = IMAGE_PATH;
    int width = 100;
    int height = 200;

    InsertImageCommand command(imagePath, width, height, std::nullopt, items);

    EXPECT_NO_THROW(command.DoExecute());

    ASSERT_EQ(items.size(), 1);
    EXPECT_TRUE(AssertDirectoryIsNotEmpty("temp"));
    std::string str = GetFirstFileOnDirectory("temp");
    std::cout << str << std::endl;
//    EXPECT_TRUE(AssertFilesAreEqual(IMAGE_PATH, "temp/" + GetFirstFileOnDirectory("temp")));
}

TEST(InsertImageCommandTests, ExecuteInsertsImageAtPositionSuccess)
{
    std::vector<CDocumentItem> items;
    std::string imagePath = IMAGE_PATH;
    int width = 100;
    int height = 200;

    InsertImageCommand command(imagePath, width, height, 0, items);

    EXPECT_NO_THROW(command.DoExecute());

    ASSERT_EQ(items.size(), 1);
    EXPECT_TRUE(AssertDirectoryIsNotEmpty("temp"));
//    EXPECT_TRUE(AssertFilesAreEqual(IMAGE_PATH, "temp/" + GetFirstFileOnDirectory("temp")));
}

TEST(InsertImageCommandTests, ExecuteThrowsOnInvalidPositionError)
{
    std::vector<CDocumentItem> items;
    std::string imagePath = IMAGE_PATH;
    int width = 100;
    int height = 200;

    InsertImageCommand command(imagePath, width, height, 2, items);

    EXPECT_THROW(command.DoExecute(), std::invalid_argument);
}

TEST(InsertImageCommandTests, UnexecuteRemovesLastInsertedSuccess)
{
    std::vector<CDocumentItem> items;
    std::string imagePath = IMAGE_PATH;
    int width = 100;
    int height = 200;

    InsertImageCommand command(imagePath, width, height, std::nullopt, items);

    command.DoExecute();
    ASSERT_EQ(items.size(), 1);
    EXPECT_TRUE(AssertDirectoryIsNotEmpty("temp"));
//    EXPECT_TRUE(AssertFilesAreEqual(IMAGE_PATH, "temp/" + GetFirstFileOnDirectory("temp")));

    command.DoUnexecute();
    ASSERT_EQ(items.size(), 0);
    EXPECT_TRUE(AssertDirectoryIsNotEmpty("temp"));
//    EXPECT_TRUE(AssertFilesAreEqual(IMAGE_PATH, "temp/" + GetFirstFileOnDirectory("temp")));
}

TEST(InsertImageCommandTests, UnexecuteRemovesInsertedAtPosition)
{
    std::vector<CDocumentItem> items;
    std::string imagePath = IMAGE_PATH;
    int width = 100;
    int height = 200;

    InsertImageCommand command(imagePath, width, height, 0, items);

    command.DoExecute();
    ASSERT_EQ(items.size(), 1);
    EXPECT_TRUE(AssertDirectoryIsNotEmpty("temp"));
//    EXPECT_TRUE(AssertFilesAreEqual(IMAGE_PATH, "temp/" + GetFirstFileOnDirectory("temp")));

    command.DoUnexecute();
    ASSERT_EQ(items.size(), 0);
    EXPECT_TRUE(AssertDirectoryIsNotEmpty("temp"));
//    EXPECT_TRUE(AssertFilesAreEqual(IMAGE_PATH, "temp/" + GetFirstFileOnDirectory("temp")));
}

TEST(InsertParagraphCommandTest, InsertAtEndSuccess)
{
    std::vector<CDocumentItem> items;
    std::string text = "New paragraph text";

    InsertParagraphCommand command(text, std::nullopt, items);

    command.DoExecute();

    ASSERT_EQ(items.size(), 1);

    auto paragraph = std::dynamic_pointer_cast<CParagraph>(items[0].GetParagraph());
    ASSERT_NE(paragraph, nullptr);
    EXPECT_EQ(paragraph->GetText(), text);

    command.DoUnexecute();

    EXPECT_TRUE(items.empty());
}

TEST(InsertParagraphCommandTest, InsertAtPositionSuccess)
{
    std::string text = "Existing paragraph";
    auto paragraph = std::make_shared<CParagraph>(text);
    CDocumentItem item(paragraph);
    std::vector<CDocumentItem> items = {item};

    std::string textInserted = "Inserted paragraph";
    size_t position = 0;

    InsertParagraphCommand command(textInserted, position, items);

    command.DoExecute();

    ASSERT_EQ(items.size(), 2);

    auto paragraph1 = std::dynamic_pointer_cast<CParagraph>(items[position].GetParagraph());
    ASSERT_NE(paragraph1, nullptr);
    EXPECT_EQ(paragraph1->GetText(), textInserted);

    command.DoUnexecute();

    ASSERT_EQ(items.size(), 1);
    EXPECT_EQ(items[0].GetParagraph()->GetText(), "Existing paragraph");
}

TEST(InsertParagraphCommandTest, InsertAtInvalidPositionError)
{
    std::vector<CDocumentItem> items;
    std::string text = "Text for invalid position";
    size_t invalidPosition = 10;

    InsertParagraphCommand command(text, invalidPosition, items);

    EXPECT_THROW(command.DoExecute(), std::invalid_argument);
    EXPECT_TRUE(items.empty());
}