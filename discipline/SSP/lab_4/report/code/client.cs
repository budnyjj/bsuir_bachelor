 using System;
 using System.Collections.Generic;
 using System.Linq;
 using System.Text;
 using System.Threading.Tasks;
 using System.Runtime.Remoting;
 using System.Runtime.Remoting.Channels;
 using System.Runtime.Remoting.Channels.Http;
 using System.Net;
 using System.Net.Sockets;
 using System.Xml.Linq;
 using System.IO;
 using System.Windows.Forms;
 using System.Xml.Serialization;

 using StudentLibrary;

 namespace Client
 {
     class Client
     {
         public static List<int> availableIDs = null;

         public static void StartClient() {

             byte[] bytes = null;
             IPAddress ipAddress = new IPAddress(new byte[] { 127, 0, 0, 1 });
             IPEndPoint remoteEndPoint = new IPEndPoint(ipAddress, 50001);

             try
             {
                 while (true) {
                     using (Socket sender = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp))
                     {
                         bytes = new byte[1048576];
                         PrintMainMenu();
                         switch (Console.ReadKey().KeyChar)
                         {
                             case '1':
                                 {
                                     Console.WriteLine();
                                     sender.Connect(remoteEndPoint);
                                     Console.WriteLine("### INFO ###: Socket connected to {0}", sender.RemoteEndPoint.ToString());

                                     string generatedRequest = generateAvailableIDsRequest();
                                     int bytesSent = sender.Send(Encoding.UTF8.GetBytes(generatedRequest));

                                     int bytesRec = sender.Receive(bytes);
                                     if (parseResponse(Encoding.UTF8.GetString(bytes, 0, bytesRec)))
                                     {
                                         PrintAvailableIDsList();
                                     }

                                     sender.Shutdown(SocketShutdown.Both);
                                     sender.Close();
                                 }
                                 break;

                             case '2':
                                 {
                                     Console.WriteLine();
                                     if (IsIDsAvailable())
                                     {
                                         int studentID;
                                         string idInString = Console.ReadLine();
                                         while(!Int32.TryParse(idInString, out studentID) || !availableIDs.Contains(studentID)) {
                                             idInString = Console.ReadLine();
                                         }

                                         sender.Connect(remoteEndPoint);
                                         Console.WriteLine("###INFO###: Socket connected to {0}", sender.RemoteEndPoint.ToString());

                                         string generatedRequest = generateStudentInfoRequest(studentID);
                                         int bytesSent = sender.Send(Encoding.UTF8.GetBytes(generatedRequest));

                                         int bytesRec = sender.Receive(bytes);
                                         if (parseResponse(Encoding.UTF8.GetString(bytes, 0, bytesRec)))
                                         {
                                             Console.WriteLine("### INFO ###: Success!");
                                         }

                                         sender.Shutdown(SocketShutdown.Both);
                                         sender.Close();
                                     }
                                 }
                                 break;
                             case 'q':
                             case 'Q':
                                 return;
                             default:
                                 break;
                         }
                     }
                 }
             } catch (ArgumentNullException ane) {
                 Console.WriteLine("ArgumentNullException : {0}", ane.ToString());
             } catch (SocketException se) {
                 Console.WriteLine("SocketException : {0}", se.ToString());
             } catch (Exception e) {
                 Console.WriteLine("Unexpected exception : {0}", e.ToString());
             }
         }

         public static string generateAvailableIDsRequest()
         {
             XElement requestXML = new XElement("request", new XAttribute("req", "getAvailableIDs"));
             return requestXML.ToString();;
         }

         public static string generateStudentInfoRequest(int studentID)
         {
             XElement requestXML = new XElement("request", new XAttribute("req", "getStudentsByID"), studentID.ToString());
             return requestXML.ToString();
         }

         public static bool parseResponse(string responseString)
         {
             bool isSuccess = false;

             XElement responseElement = XElement.Parse(responseString);
             string rootName = responseElement.AncestorsAndSelf().First().Name.ToString();
             if (rootName.Equals("response"))
             {
                 string attribute = responseElement.Attribute("req").Value;
                 if (attribute.Equals("getAvailableIDs"))
                 {
                     isSuccess = true;
                     if (availableIDs != null)
                     {
                         availableIDs.Clear();
                     }
                     else
                     {
                         availableIDs = new List<int>();
                     }

                     foreach (XElement element in responseElement.Nodes())
                     {
                         availableIDs.Add(Convert.ToInt32(element.Value));
                     }
                 }
                 else if (attribute.Equals("getStudentsByID"))
                 {
                     if (responseElement.Value.Trim() != "")
                     {
                         foreach (XElement studentInfoElement in responseElement.Elements())
                         {
                             XmlSerializer deserializer = new XmlSerializer(typeof(Student));
                             using (StringReader stringReader = new StringReader(studentInfoElement.Element("info").Value))
                             {
                                 Student student = (Student)deserializer.Deserialize(stringReader);
                                 if (student != null)
                                 {
                                     Console.WriteLine(student.ToString());
                                     isSuccess = true;
                                 }
                             }

                             if (!studentInfoElement.Element("photo").IsEmpty)
                             {
                                 string photoInBase64String = studentInfoElement.Element("photo").Value;

                                 using (SaveFileDialog saveFileDialog = new SaveFileDialog())
                                 {
                                     saveFileDialog.FileName = "sample";
                                     saveFileDialog.DefaultExt = "png";
                                     if (saveFileDialog.ShowDialog() == DialogResult.OK)
                                     {
                                         File.WriteAllBytes(saveFileDialog.FileName, Convert.FromBase64String(photoInBase64String));
                                     }
                                 }
                                 Console.WriteLine("= = = = = = = = = = = = = = = = = = = = = = = = = = =");
                             }
                         }
                     }
                 }
             }

             return isSuccess;
         }

         public static string generateRequestByLastName(string lastName)
         {
             XElement requestXML = new XElement("request",
                                     new XElement("lastname", lastName)
                                   );
             return requestXML.ToString();
         }

         static byte[] GetBytesFromString(string str)
         {
             byte[] bytes = new byte[str.Length * sizeof(char)];
             System.Buffer.BlockCopy(str.ToCharArray(), 0, bytes, 0, bytes.Length);
             return bytes;
         }

         static void PrintMainMenu()
         {
             Console.WriteLine("= = = = = = = = = = = = = = = = = = = = = = = = = = =");
             Console.WriteLine("1) Show available student's IDs");
             Console.WriteLine("2) Show student info by ID");
             Console.WriteLine("q) Quit");
             Console.WriteLine("= = = = = = = = = = = = = = = = = = = = = = = = = = =");
         }

         static bool IsIDsAvailable()
         {
             return ((availableIDs != null) && (availableIDs.Count != 0)) ? true : false;
         }

         static void PrintAvailableIDsList()
         {
             if (IsIDsAvailable())
             {
                 foreach (int id in availableIDs)
                 {
                     Console.WriteLine(" ID: " + id.ToString());
                 }
             }
         }

         [STAThread]
         static void Main(string[] args)
         {
             StartClient();
             Console.Read();
         }
     }
 }
