 /* interface IStudentOperations */

 using System;
 using System.Collections.Generic;
 using System.Linq;
 using System.ServiceModel;
 using System.Text;
 using System.Threading.Tasks;

 namespace StudentLibrary
 {
     [ServiceContract]
     public interface IStudentOperations
     {
         [OperationContract]
         List<int> getAvailableIDs();

         [OperationContract]
         List<Student> getStudentsByID(int id);
     }
 }


 /* class Student */

 using System;
 using System.Collections.Generic;
 using System.Linq;
 using System.Text;
 using System.Threading.Tasks;
 using System.Runtime.Serialization;
 using System.ServiceModel;
 using System.Xml.Serialization;

 namespace StudentLibrary
 {
     [XmlRoot("student")]
     [DataContract]
     public class Student
     {
         [DataMember]
         [XmlAttribute("id")]
         private long    id;

         [DataMember]
         [XmlElement("firstName")]
         private string  firstName;

         [DataMember]
         [XmlElement("lastName")]
         private string  lastName;

         [DataMember]
         [XmlElement("groupNumber")]
         private long    groupNumber;

         [DataMember]
         [XmlElement("course")]
         private byte    course;

         [DataMember]
         [XmlElement("averageScore")]
         private double  averageScore;

         [DataMember]
         [XmlIgnore]
         private string  photoPath;

         public long Id
         {
             get { return id; }
             set { id = value; }
         }

         public string FirstName
         {
             get { return firstName; }
             set { firstName = value; }
         }

         public string LastName
         {
             get { return lastName; }
             set { lastName = value; }
         }

         public long GroupNumber
         {
             get { return groupNumber; }
             set { groupNumber = value; }
         }

         public byte Course
         {
             get { return course; }
             set { course = value; }
         }

         public double AverageScore
         {
             get { return averageScore; }
             set { averageScore = value; }
         }

         public string PhotoPath
         {
             get { return photoPath; }
             set { photoPath = value; }
         }

         public override string ToString()
         {
             return "= = = = = Data about student with ID = " + id.ToString() + " = = = = =\n" +
                    " Full name: " + firstName + " " + lastName + "\n" +
                    " Group number: " + groupNumber.ToString() + "\n" +
                    " Course: " + course.ToString() + "\n" +
                    " Average score: " + String.Format("{0:0.#}", averageScore) + "\n" +
                    "= = = = = = = = = = = = = = = = = = = = = = = = = = =";
         }
     }
 }
