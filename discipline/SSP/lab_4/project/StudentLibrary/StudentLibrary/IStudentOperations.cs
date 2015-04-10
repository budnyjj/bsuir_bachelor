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
