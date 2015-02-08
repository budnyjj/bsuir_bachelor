using System;
using System.IO;
using Gtk;
using Glade;

// Controller class
public class BookShelfApp
{
  [Widget]
  Gtk.Window MainWindow;
  
  [Widget]
  Button quitButton;

  [Widget]
  TreeView treeView;

  [Widget]
  TextView textView;

  BookShelfModel bookShelfModel = new BookShelfModel("books", "txt");
    
  public static void Main(string[] args)
  {
    new BookShelfApp(args);
  }
  
  public BookShelfApp(string[] args)
  {
    Application.Init();
    
    Glade.XML gxml = new Glade.XML(null, "ui.glade", "mainWindow", null);
    gxml.Autoconnect(this);

    treeView.AppendColumn("Books", new CellRendererText(), "text", 0);
    treeView.HeadersVisible = true;

    treeView.Selection.Changed += onSelectBook;
    
    treeView.Model = bookShelfModel.bookList;
    
    Application.Run();
  }
  
  public void onWindowDelete(object obj, EventArgs args)
  {
    Application.Quit();
  }

  public void onSelectBook(object obj, EventArgs args)
  {
    TreeIter iter;
    TreeModel model;
    
    if (((TreeSelection) obj).GetSelected(out model, out iter))
      {
        String bookName = (String) model.GetValue(iter, 0);
        String bookDescription = bookShelfModel.getBookDescription(bookName);
        textView.Buffer.Text = bookDescription;
      }
  }

  public void onChooseBookDir(object obj, EventArgs args)
  {
    Gtk.FileChooserDialog fc =
      new Gtk.FileChooserDialog("Choose directory with books",
                                MainWindow,
                                FileChooserAction.SelectFolder,
                                "Cancel",ResponseType.Cancel,
                                "Open",ResponseType.Accept);

    if (fc.Run() == (int) ResponseType.Accept)
      {
        bookShelfModel.bookDir = fc.Filename;
        treeView.Model = bookShelfModel.bookList;
      }

    fc.Destroy();
  }
}