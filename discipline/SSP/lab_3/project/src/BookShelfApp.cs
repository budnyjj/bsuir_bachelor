using System;
using System.IO;
using Gtk;
using Glade;

// Controller class
public class BookShelfApp
{
  [Widget]
  Gtk.Window mainWindow;
  
  [Widget]
  Button createBookRecordButton;

  [Widget]
  Button updateBookRecordButton;

  [Widget]
  Button deleteBookRecordButton;

  [Widget]
  TreeView bookRecordsTreeView;

  [Widget]
  Entry bookTitleEntry;
  
  [Widget]
  Entry bookAuthorEntry;

  [Widget]
  Entry bookYearEntry;

  [Widget]
  TextView bookDescriptionTextView;

  BookShelfModel bookShelfModel = new BookShelfModel();
    
  public static void Main(string[] args)
  {
    new BookShelfApp(args);
  }
  
  public BookShelfApp(string[] args)
  {
    Application.Init();
    
    Glade.XML gxml = new Glade.XML(null, "ui.glade", "mainWindow", null);
    gxml.Autoconnect(this);

    bookRecordsTreeView.AppendColumn("Title", new CellRendererText(), "text", 0);
    bookRecordsTreeView.AppendColumn("Author", new CellRendererText(), "text", 1);
    bookRecordsTreeView.AppendColumn("Year", new CellRendererText(), "text", 2);
    bookRecordsTreeView.Selection.Changed += onReadBookRecord;
    
    Application.Run();
  }
  
  public void onWindowDestroy(object obj, EventArgs args)
  {
    Application.Quit();
  }

  public void onReadBookRecord(object obj, EventArgs args)
  {
    TreeSelection bookRecordSelection = bookRecordsTreeView.Selection;
    
    TreeIter iter;
    TreeModel model;
    
    if (bookRecordSelection.GetSelected(out model, out iter))
      {
        String bookTitle = (String) model.GetValue(iter, 0);
        String bookAuthor = (String) model.GetValue(iter, 1);
        String bookYear = (String) model.GetValue(iter, 2);

        bookTitleEntry.Text = bookTitle;
        bookAuthorEntry.Text = bookAuthor;
        bookYearEntry.Text = bookYear;
        
        String bookDescription = bookShelfModel.getBookDescription(bookTitle);
        bookDescriptionTextView.Buffer.Text = bookDescription;
      }
  }

  public void onCreateBookRecord(object obj, EventArgs args)
  {
    String bookTitle = bookTitleEntry.Text;
    String bookAuthor = bookAuthorEntry.Text;
    String bookYear = bookYearEntry.Text;
    String bookDescription = bookDescriptionTextView.Buffer.Text;

    try
      {
        bookShelfModel.insertBook(bookTitle, bookAuthor, bookYear, bookDescription);        
      }
    catch (ArgumentException)
      {
        MessageDialog md = new MessageDialog(mainWindow,
                                             DialogFlags.DestroyWithParent,
                                             MessageType.Error,
                                             ButtonsType.Close,
                                             "Book title should be unique!");
        md.Run();
        md.Destroy();
      }
    
    bookShelfModel.refreshBookRecordsStore();
  }

  public void onUpdateBookRecord(object obj, EventArgs args)
  {
    TreeSelection bookRecordSelection = bookRecordsTreeView.Selection;
    
    TreeIter iter;
    TreeModel model;

    if (bookRecordSelection.GetSelected(out model, out iter))
      {
        String oldBookTitle = (String) model.GetValue(iter, 0);

        String newBookTitle = bookTitleEntry.Text;
        String newBookAuthor = bookAuthorEntry.Text;
        String newBookYear = bookYearEntry.Text;
        String newBookDescription = bookDescriptionTextView.Buffer.Text;

        try
          {
            bookShelfModel.updateBook(oldBookTitle,
                                      newBookTitle, newBookAuthor,
                                      newBookYear, newBookDescription);
          }
        catch (ArgumentException)
          {
            MessageDialog md = new MessageDialog(mainWindow,
                                                 DialogFlags.DestroyWithParent,
                                                 MessageType.Error,
                                                 ButtonsType.Close,
                                                 "Book title should be unique!");
            md.Run();
            md.Destroy();
          }
       
        bookShelfModel.refreshBookRecordsStore();
      }
    else
      {
        MessageDialog md = new MessageDialog(mainWindow,
                                             DialogFlags.DestroyWithParent,
                                             MessageType.Error,
                                             ButtonsType.Close,
                                             "Please, select book to update!");
        md.Run();
        md.Destroy();
      }
  }

  public void onDeleteBookRecord(object obj, EventArgs args)
  {
    TreeSelection bookRecordSelection = bookRecordsTreeView.Selection;

    TreeIter iter;
    TreeModel model;
    
    if (bookRecordSelection.GetSelected(out model, out iter))
      {
        String bookTitle = (String) model.GetValue(iter, 0);
        bookShelfModel.deleteBook(bookTitle);

        bookShelfModel.refreshBookRecordsStore();
      }
    else
      {
        MessageDialog md = new MessageDialog(mainWindow,
                                             DialogFlags.DestroyWithParent,
                                             MessageType.Error,
                                             ButtonsType.Close,
                                             "Please, select book to delete!");
        md.Run();
        md.Destroy();
      }
  }
  
  public void onChooseDatabase(object obj, EventArgs args)
  {
    Gtk.FileChooserDialog fc =
      new Gtk.FileChooserDialog("Choose books database",
                                mainWindow,
                                FileChooserAction.Open,
                                "Cancel", ResponseType.Cancel,
                                "Open", ResponseType.Accept);

    fc.Filter = new FileFilter();
    fc.Filter.AddPattern("*.sqlite");

    while (fc.Run() == (int) ResponseType.Accept)
      {
        bookShelfModel.openDatabase(fc.Filename);
        bookRecordsTreeView.Model = bookShelfModel.getBookRecordsStore();

        try
          {
            bookShelfModel.refreshBookRecordsStore();            

            createBookRecordButton.Sensitive = true;
            updateBookRecordButton.Sensitive = true;
            deleteBookRecordButton.Sensitive = true;

            break;
          }
        catch (AccessViolationException)
          {
            MessageDialog md = new MessageDialog(mainWindow,
                                                 DialogFlags.DestroyWithParent,
                                                 MessageType.Error,
                                                 ButtonsType.Close,
                                                 "Incorrect database structure! " +
                                                 "Please, select another database");
            md.Run();
            md.Destroy();
          }
      }
    fc.Destroy();
  }
}