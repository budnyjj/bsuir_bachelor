Option Explicit
Dim conn, isConnOpened, students, library

isConnOpened = False

Sub openConnection(dbPath)
        Dim strConnection
        Set conn = CreateObject("ADODB.Connection")
	strConnection = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source="

	conn.Open strConnection & dbPath
End Sub

Sub closeConnection
       conn.Close
       isConnOpened = False
End Sub

Function request(ByRef connection, requestStr)
    Set request = CreateObject("ADODB.Recordset")
    request.Open requestStr, connection, 2
End function

Sub openDatabase
    If isConnOpened = False Then
       Dim dbPath	
       dbPath = document.main_form.db_path.value
       call openConnection(dbPath)

       set students = request(conn, "SELECT * FROM students")
       set library = request(conn, "SELECT * FROM library")

       printStudent(students)

       isConnOpened = True
    else
       MsgBox("Database is already opened!")
    end if
End Sub

Sub closeDatabase
    If isConnOpened = True Then	
       call closeConnection
       set students = nothing
       set library = nothing 

       call clearStudentFields

       isConnOpened = False
    else
       MsgBox("Database is already closed!")
    end if
End Sub

Sub nextRow(ByRef rs)
    if rs.EOF = false then
       rs.moveNext
       if rs.EOF=true then
       	  rs.moveFirst
       end if
    else
	rs.moveFirst
    end if
End Sub

Sub previousRow(ByRef rs)
	if rs.BOF = false then
		rs.movePrevious
		if rs.BOF=true then
			rs.moveLast
		end if
	else
		rs.moveLast
	end if
End Sub

' === Students ===

Sub nextStudent
    If isConnOpened Then
       call nextRow(students)
       printStudent(students)
    else
       msgBox("Databse is closed!")
    End If
End Sub

Sub previousStudent
    If isConnOpened Then
       call previousRow(students)
       printStudent(students)
    else
       msgBox("Databse is closed!")
    End If
End Sub

Sub printStudent(ByRef rs)
	document.main_form.Surname.value = rs("surname")
	document.main_form.Group.value = rs("group")
	document.main_form.Age.value = rs("age")
	document.main_form.Mark.value = rs("mark")
	document.main_form.PhotoPath.value = rs("photo_path")
        document.main_form.Photo.src=rs("photo_path")
End Sub

' Maintanance

Sub clearStudentFields
	document.main_form.Surname.value = ""
	document.main_form.Group.value = ""
	document.main_form.Age.value = ""
	document.main_form.Mark.value = ""
	document.main_form.PhotoPath.value = ""
        document.main_form.Photo.src="static/img/default.jpg"
End Sub