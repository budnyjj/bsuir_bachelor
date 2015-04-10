 using System;
 using System.Collections.Generic;
 using System.Data.OleDb;
 using System.Linq;
 using System.Text;
 using System.Threading.Tasks;
 using System.Net;
 using System.Net.Sockets;
 using System.Xml.Linq;
 using System.Data;

 using StudentLibrary;
 using System.Xml.Serialization;
 using System.IO;

 namespace Server
 {
     class StudentOperationsImpl : IStudentOperations
     {
         public static string DB_PATH = @"..\..\..\db\";
         public static string TABLE_NAME = @"students";
         public static OleDbConnection connection;

         public void startListening()
         {
             IPAddress ipAddress = new IPAddress(new byte[] { 127, 0, 0, 1 });
             IPEndPoint localEndPoint = new IPEndPoint(ipAddress, 50001);

             Socket listener = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
             listener.Bind(localEndPoint);
             listener.Listen(10);

             try
             {
                 while (true)
                 {
                     Socket handler = listener.Accept();
                     byte[] bytes = new byte[1048576];
                     int bytesRec = handler.Receive(bytes);
                     string receivedRequest = Encoding.UTF8.GetString(bytes, 0, bytesRec);

                     string response = parseRequestAndGenerateResponse(receivedRequest);
                     handler.Send(Encoding.UTF8.GetBytes(response));

                     handler.Shutdown(SocketShutdown.Both);
                     handler.Close();
                 }
             }
             catch (Exception e)
             {
                 Console.WriteLine(e.ToString());
             }
         }

         string parseRequestAndGenerateResponse(string request)
         {
             string response = null;

             XElement xElement = XElement.Parse(request);
             string rootName = xElement.AncestorsAndSelf().First().Name.ToString();
             if (rootName.Equals("request"))
             {
                 string attribute = xElement.Attribute("req").Value;
                 if (attribute.Equals("getAvailableIDs"))
                 {
                     response = generateAvailableIDsResponse(getAvailableIDs());
                     Console.WriteLine(response);
                 }
                 else if (attribute.Equals("getStudentsByID"))
                 {
                     int studentID = Int32.Parse(xElement.Value);
                     response = generateStudentResponse(studentID);
                     Console.WriteLine(response);
                 }
             }
             return response;
         }

         public string generateAvailableIDsResponse(List<int> ids)
         {
             XElement responseXML = new XElement("response", new XAttribute("req", "getAvailableIDs"));

             foreach (int id in ids)
             {
                 responseXML.Add(new XElement("id", id.ToString()));
             }

             return responseXML.ToString();
         }

         public string generateStudentResponse(int studentID)
         {
             XElement responseXML = new XElement("response", new XAttribute("req", "getStudentsByID"), new XAttribute("id", studentID.ToString()));

             List<Student> students = getStudentsByID(studentID);
             if (students != null && students.Count != 0)
             {
                 foreach (Student student in students)
                 {
                     responseXML.Add(new XElement("studentInfo"));

                     XmlSerializer serializer = new XmlSerializer(typeof(Student));
                     using (StringWriter sw = new StringWriter())
                     {
                         serializer.Serialize(sw, student);
                         responseXML.Element("studentInfo").Add(new XElement("info", sw.ToString()));
                     }

                     if (student.PhotoPath != null && student.PhotoPath.Trim() != "")
                     {
                         string pathToExe = AppDomain.CurrentDomain.BaseDirectory;
                         string pathToDB = Path.Combine(pathToExe, DB_PATH);
                         string fullPhotoPath = Path.Combine(pathToDB, student.PhotoPath);

                         string photoInBase64String = Convert.ToBase64String(File.ReadAllBytes(fullPhotoPath));
                         responseXML.Element("studentInfo").Add(new XElement("photo", photoInBase64String));
                     }
                     else
                     {
                         responseXML.Element("studentInfo").Add(new XElement("photo"));
                     }
                 }
             }
             return responseXML.ToString();
         }

         public List<int> getAvailableIDs()
         {
             List<int> resultList = new List<int>();

             connection.Open();
             string selectQuery = @"SELECT * FROM " + TABLE_NAME;
             OleDbDataAdapter dataAdapter = new OleDbDataAdapter(selectQuery, connection);
             dataAdapter.SelectCommand = new OleDbCommand(selectQuery, connection);
             DataTable dataTable = new DataTable(TABLE_NAME);
             dataAdapter.Fill(dataTable);

             resultList = dataTable.Rows.OfType<DataRow>().Select(dr => dr.Field<int>("id")).ToList();

             connection.Close();
             return resultList;
         }

         public List<Student> getStudentsByID(int id)
         {
             connection.Open();
             string selectQuery = @"SELECT * FROM " + TABLE_NAME + @" WHERE id=" + id.ToString();
             OleDbDataAdapter dataAdapter = new OleDbDataAdapter(selectQuery, connection);
             dataAdapter.SelectCommand = new OleDbCommand(selectQuery, connection);
             DataTable dataTable = new DataTable(TABLE_NAME);
             dataAdapter.Fill(dataTable);

             List<Student> students = (from c in dataTable.AsEnumerable()
                                       select new Student {
                                           Id = c.Field<int>("id"),
                                           FirstName = c.Field<string>("firstName"),
                                           LastName = c.Field<string>("lastName"),
                                           GroupNumber = c.Field<int>("groupNumber"),
                                           Course = c.Field<byte>("course"),
                                           AverageScore = c.Field<float>("averageScore"),
                                           PhotoPath = c.Field<string>("photoPath")
                                       }).ToList();

             connection.Close();
             return students;
         }

         static void Main(string[] args)
         {
             // Database configuration
             const string provider = @"Microsoft.Jet.OLEDB.4.0";
             const string dbName = @"students_db.mdb";
             string pathToExe = AppDomain.CurrentDomain.BaseDirectory;
             string dataSource = Path.Combine(pathToExe, DB_PATH, dbName);

             string connectionString = String.Concat(@"provider=", provider, @";data source=", dataSource);
             connection = new OleDbConnection(connectionString);

             // StudentOperations implementation
             StudentOperationsImpl studentOperations = new StudentOperationsImpl();
             studentOperations.startListening();
         }
     }
 }
