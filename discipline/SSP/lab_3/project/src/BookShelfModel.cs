using System;
using Mono.Data.Sqlite;
using Gtk;

// Model class
public class BookShelfModel
{
  ListStore bookRecordsList = new ListStore(
    typeof(string), // Title
    typeof(string), // Author
    typeof(string)  // Year
  );

  SqliteConnection dbConnection = null;
  
  public void openDatabase(String databasePath)
  {
    String connectionString = "URI=file:" + databasePath;
    dbConnection =  new SqliteConnection(connectionString);
  }

  public ListStore getBookRecordsStore()
  {
    return bookRecordsList;
  }

  public void refreshBookRecordsStore()
  {
    bookRecordsList.Clear();
      
    try
      {           
        dbConnection.Open();

        String queryString = "SELECT Title, Author, Year FROM Books";

        using (SqliteCommand cmd = new SqliteCommand(queryString, dbConnection))
          {
            using (SqliteDataReader rdr = cmd.ExecuteReader())
              {
                while (rdr.Read())
                  {
                    bookRecordsList.AppendValues(rdr["Title"].ToString(),
                                                 rdr["Author"].ToString(),
                                                 rdr["Year"].ToString());                    
                  }
              }
          }
      }
    catch (Mono.Data.Sqlite.SqliteException ex)
      {
        Console.WriteLine(ex);
        throw new AccessViolationException("Incorrect database structure", ex);
      }
    finally
      {        
        dbConnection.Close();
      }
  }

  public String getBookDescription(String bookTitle)
  {
    String bookDescription = "";
    try
      {        
        dbConnection.Open();

        String queryString = String.Format("SELECT Description FROM Books WHERE Title='{0}'",
                                           bookTitle);
            
        using (SqliteCommand cmd = new SqliteCommand(queryString, dbConnection))
          {
            using (SqliteDataReader rdr = cmd.ExecuteReader())
              {
                rdr.Read();
                bookDescription = rdr["Description"].ToString();
              }
          }
      }
    catch (Mono.Data.Sqlite.SqliteException ex)
      {
        Console.WriteLine(ex);
      }
    finally
      {
        dbConnection.Close();
      }
    
    return bookDescription;
  }

  public void insertBook(String bookTitle, String bookAuthor, String bookYear, String bookDescription)
  {
    try
      {        
        dbConnection.Open();

        String queryString = String.Format("INSERT INTO Books VALUES ('{0}', '{1}', {2}, '{3}')",
                                           escapeQuotes(bookTitle),
                                           escapeQuotes(bookAuthor),
                                           Convert.ToInt32(bookYear),
                                           escapeQuotes(bookDescription));
        
        using (SqliteCommand cmd = new SqliteCommand(queryString, dbConnection))
          {
            cmd.ExecuteNonQuery();
          }
      }
    catch (Mono.Data.Sqlite.SqliteException ex)
      {
        Console.WriteLine(ex);
        throw new ArgumentException("Constraint violation", ex);
      }
    finally
      {
        dbConnection.Close();
      }
  }  

  public void updateBook(String oldBookTitle,
                         String newBookTitle, String newBookAuthor,
                         String newBookYear, String newBookDescription)
  {
    try
      {        
        dbConnection.Open();

        String queryString =
          String.Format("UPDATE Books SET Title='{0}', Author='{1}', " +
                        "Year={2}, Description='{3}' WHERE Title='{4}'",
                        escapeQuotes(newBookTitle), escapeQuotes(newBookAuthor), 
                        Convert.ToInt32(newBookYear), escapeQuotes(newBookDescription),
                        escapeQuotes(oldBookTitle));
        
        using (SqliteCommand cmd = new SqliteCommand(queryString, dbConnection))
          {
            cmd.ExecuteNonQuery();
          }
      }
    catch (Mono.Data.Sqlite.SqliteException ex)
      {
        throw new ArgumentException("Constraint violation", ex);
        Console.WriteLine(ex);
      }
    finally
      {
        dbConnection.Close();
      }
  }  

  public void deleteBook(String bookTitle)
  {
    try
      {        
        dbConnection.Open();

        String queryString = String.Format("DELETE FROM Books WHERE Title='{0}'",
                                           bookTitle);
            
        using (SqliteCommand cmd = new SqliteCommand(queryString, dbConnection))
          {
            cmd.ExecuteNonQuery();
          }
      }
    catch (Mono.Data.Sqlite.SqliteException ex)
      {
        Console.WriteLine(ex);
      }
    finally
      {
        dbConnection.Close();
      }
  }

  private String escapeQuotes(String s)
  {
    return s.Replace("'", "''");
  }
}