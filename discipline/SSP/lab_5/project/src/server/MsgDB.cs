using System;
using System.Collections.Generic;
using Mono.Data.Sqlite;

// Model class
public class MsgDB
{
  SqliteConnection dbCon = null;
  
  public MsgDB(String dbPath)
  {
    dbCon = new SqliteConnection("URI=file:" + dbPath);
    
    try
      {
        dbCon.Open();

        using (SqliteCommand dbCmd = new SqliteCommand(dbCon))
          {            
            dbCmd.CommandText = "DROP TABLE IF EXISTS Messages";
            dbCmd.ExecuteNonQuery();

            dbCmd.CommandText = "CREATE TABLE Messages " +
              "(" +
              "ID INTEGER PRIMARY KEY AUTOINCREMENT, " +
              "Sender TEXT, Content TEXT, Timestamp DATETIME" +
              ")";
            dbCmd.ExecuteNonQuery();
          }
      }
    catch (SqliteException ex)
      {
        Console.WriteLine(ex);
      }
    finally
      {
        dbCon.Close();  
      }
  }

  public List<Message> selectMessages(DateTime fromDate)
  {
    List<Message> messages = new List<Message>();
    
    try
      {           
        dbCon.Open();

        String queryString = "SELECT Sender, Content, Timestamp " +
          "FROM Messages WHERE Timestamp >= @Timestamp";

        using (SqliteCommand selectCmd =  new SqliteCommand(queryString, dbCon))
          {            
            selectCmd.Parameters.AddWithValue("@Timestamp", fromDate);
            
            using (SqliteDataReader rdr = selectCmd.ExecuteReader())
              {
                while (rdr.Read())
                  {
                    messages.Add(new Message(rdr["Sender"].ToString(),
                                             rdr["Content"].ToString(),
                                             (DateTime) rdr["Timestamp"]));
                  }
              }
          }
      }
    catch (SqliteException ex)
      {
        Console.WriteLine(ex);
      }
    finally
      {        
        dbCon.Close();
      }

    return messages;
  }

  public void insertMessage(Message msg)
  {
    try
      {        
        dbCon.Open();

        String queryString = "INSERT INTO Messages " +
                             "(Sender, Content, Timestamp) " +
                             "VALUES (@Sender, @Content, @Timestamp)";

        using (SqliteCommand insertCmd = new SqliteCommand(queryString, dbCon))
          {            
            insertCmd.Parameters.AddWithValue("@Sender", msg.Sender);
            insertCmd.Parameters.AddWithValue("@Content", msg.Content);
            insertCmd.Parameters.AddWithValue("@Timestamp", msg.Timestamp);
        
            insertCmd.ExecuteNonQuery();
          }        
      }
    catch (SqliteException ex)
      {
        Console.WriteLine(ex);
      }
    finally
      {
        dbCon.Close();
      }
  }
}