using System;
using System.IO;
using Gtk;

// Model class
public class BookShelfModel
{
  String _bookDir;
  String _bookExt;
  ListStore _bookList = new ListStore(typeof(string));
  
  public String bookDir
  {
    get
      {
        return _bookDir;
      }
    set
      {
        _bookDir = value;
      }
  }

  public ListStore bookList
  {
    get
      {
        // drop old records from _bookList
        _bookList.Clear();
       
        DirectoryInfo bookDirInfo = new DirectoryInfo(_bookDir);    
        FileInfo[] books = bookDirInfo.GetFiles("*." + _bookExt);
    
        foreach (FileInfo book in books)
          {
            // drop extension from filename
            String bookName =
              book.Name.Substring(0, book.Name.Length - book.Extension.Length);
        
            _bookList.AppendValues(bookName);
          }

        return _bookList;
      }
  }

  
  public BookShelfModel(String bookDir, String bookExt)
  {
    _bookDir = bookDir;
    _bookExt = bookExt;
  }
  
  public String getBookDescription(String bookName, int numLines = 10, int lineWidth = 72)
  {
    String description = "";

    // append extension
    String fileName = bookName + "." + _bookExt;
    
    // obtain path to book
    String bookPath = Path.Combine(_bookDir, fileName);

    // check, if file exists
    if (!File.Exists(bookPath))
      {
        description = "There is no such book...";
      }
    else
      {
        using (StreamReader sr = File.OpenText(bookPath))
          {
            String curLine;
            for (int i = 0; i < numLines; i++)
              {
                if ((curLine = sr.ReadLine()) != null)
                  {
                    description += curLine + "\n";                    
                  }
                else
                  {
                    break;                    
                  }
              }
          } 
      }
    return description;
  }
}