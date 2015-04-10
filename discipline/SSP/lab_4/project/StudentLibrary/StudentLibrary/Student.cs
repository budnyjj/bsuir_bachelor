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
            return "= = = = = Данные о студенте с ID = " + id.ToString() + " = = = = =\n" +
                   " Полное имя: " + firstName + " " + lastName + "\n" +
                   " Номер группы: " + groupNumber.ToString() + "\n" +
                   " Курс обучения: " + course.ToString() + "\n" +
                   " Средний балл: " + String.Format("{0:0.#}", averageScore) + "\n" +
                   "= = = = = = = = = = = = = = = = = = = = = = = = = = =";
        }
    }
}
