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
    catch (SqliteException ex)
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
    catch (SqliteException ex)
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

        SqliteCommand insertCmd = new SqliteCommand("INSERT INTO Books " +
                                                    "(Title, Author, Year, Description) " +
                                                    "VALUES (@bookTitle, @bookAuthor, @bookYear, @bookDescription)",
                                                    dbConnection);

        insertCmd.Parameters.AddWithValue("@bookTitle", bookTitle);
        insertCmd.Parameters.AddWithValue("@bookAuthor", bookAuthor);
        insertCmd.Parameters.AddWithValue("@bookYear", bookYear);
        insertCmd.Parameters.AddWithValue("@bookDescription", bookDescription);
        
        insertCmd.ExecuteNonQuery();
      }
    catch (SqliteException ex)
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

        SqliteCommand updateCmd = new SqliteCommand("UPDATE Books SET " +
                                                    "Title=@newBookTitle, " +
                                                    "Author=@newBookAuthor, " +
                                                    "Year=@newBookYear, " +
                                                    "Description=@newBookDescription " +
                                                    "WHERE Title=@oldBookTitle",
                                                    dbConnection);

        updateCmd.Parameters.AddWithValue("@newBookTitle", newBookTitle);
        updateCmd.Parameters.AddWithValue("@newBookAuthor", newBookAuthor);
        updateCmd.Parameters.AddWithValue("@newBookYear", newBookYear);
        updateCmd.Parameters.AddWithValue("@newBookDescription", newBookDescription);
        updateCmd.Parameters.AddWithValue("@oldBookTitle", oldBookTitle);

        updateCmd.ExecuteNonQuery();

      }
    catch (SqliteException ex)
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

        SqliteCommand deleteCmd = new SqliteCommand("DELETE FROM Books WHERE Title=@bookTitle",
                                                    dbConnection);

        deleteCmd.Parameters.AddWithValue("@bookTitle", bookTitle);

        deleteCmd.ExecuteNonQuery();

      }
    catch (SqliteException ex)
      {
        Console.WriteLine(ex);
      }
    finally
      {
        dbConnection.Close();
      }
  }
}