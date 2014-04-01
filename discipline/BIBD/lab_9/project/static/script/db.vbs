Option Explicit
Dim conn, isConnOpened, students, library

Dim adOpenKeyset, adLockOptimistic, adUseServer
adOpenKeyset = 2
adLockOptimistic = 3
adUseServer = 2

isConnOpened = False


' === DB interface ===

Sub openDatabase
    If isConnOpened = False Then
       Dim dbPath
       dbPath = document.students_form.db_path.value
       call openConnection(dbPath)

       set students = request(conn, "SELECT * FROM students")
       set library = request(conn, "SELECT * FROM library")

       printStudent(students)
       printBook(library)

       isConnOpened = True
    else
       MsgBox("Database is already opened!")
    End if
End Sub

Sub closeDatabase
    If isConnOpened = True Then
       call closeConnection
       set students = nothing
       set library = nothing

       isConnOpened = False
    Else
       MsgBox("Database is already closed!")
    End if

    call clearStudentFields
    call clearLibraryFields
End Sub

' === DB internals ===

Sub openConnection(dbPath)
    Set conn = CreateObject("ADODB.Connection")
    With conn
     .Provider = "Microsoft.Access.OLEDB.10.0"
     .Properties("Data Provider").Value = "Microsoft.Jet.OLEDB.4.0"
     .Properties("Data Source").Value = dbPath
     .Open
    End With
End Sub

Sub closeConnection
    conn.Close
    isConnOpened = False
End Sub

Function request(ByRef connection, requestStr)
    Set request = CreateObject("ADODB.Recordset")
    With request
         .ActiveConnection = connection
     .Source = requestStr
     .CursorType = adOpenKeyset
     .LockType = adLockOptimistic
     .CursorLocation = adUseServer
     .Open
    End With
End function

Sub nextRow(ByRef rs)
    If rs.EOF = false then
       rs.moveNext
       If rs.EOF=true then
          rs.moveFirst
       End if
    Else
        If (rs.BOF = false) Then
	   rs.moveFirst
	End If
    End if
End Sub

Sub previousRow(ByRef rs)
    If rs.BOF = false then
        rs.movePrevious
        If rs.BOF=true then
            rs.moveLast
        End if
    else
	If (rs.EOF = false) Then
           rs.moveLast
	End If
    End if
End Sub

Sub deleteRow(ByRef rs)
    rs.Delete
    rs.Update
End Sub

Sub insertRow(ByRef rs, ByRef fields, ByRef values)
  rs.AddNew fields, values
  rs.Update
End Sub

Sub updateRow(ByRef rs, ByRef fields, ByRef values)
  rs.Update fields, values
  rs.Update
End Sub

' === Students interface ===

Sub nextStudent
    If isConnOpened Then
       call nextRow(students)
       printStudent(students)
    else
       call connErrorMsg
    End If
End Sub

Sub previousStudent
    If isConnOpened Then
       call previousRow(students)
       printStudent(students)
    else
       call connErrorMsg
    End If
End Sub

Sub deleteStudent
    If isConnOpened Then
        deleteRow(students)
        nextRow(students)
        printStudent(students)
    Else
        call connErrorMsg
    End If
End Sub

Sub insertStudent
    If isConnOpened Then
        Dim fieldsArray(5)
        Dim values(5)
        Dim maxStudID

        fieldsArray(0) = "studID"
        fieldsArray(1) = "surname"
        fieldsArray(2) = "group"
        fieldsArray(3) = "age"
        fieldsArray(4) = "mark"
        fieldsArray(5) = "photo_path"

        ' select max studId from DB
        maxStudID = request(conn, "SELECT MAX(studID) AS studID FROM students")

        values(0) = maxStudID("studID").value + 1
        values(1) = document.students_form.Surname.value
        values(2) = document.students_form.Group.value
        values(3) = document.students_form.Age.value
        values(4) = document.students_form.Mark.value
        values(5) = document.students_form.PhotoPath.value

        call insertRow(students, fieldsArray, values)
        call printStudent(students)
    Else
        call connErrorMsg
    End If
End Sub

Sub updateStudent
    If isConnOpened Then
        Dim fieldsArray(4)
        Dim values(4)

        fieldsArray(0) = "surname"
        fieldsArray(1) = "group"
        fieldsArray(2) = "age"
        fieldsArray(3) = "mark"
        fieldsArray(4) = "photo_path"

        values(0) = document.students_form.Surname.value
        values(1) = document.students_form.Group.value
        values(2) = document.students_form.Age.value
        values(3) = document.students_form.Mark.value
        values(4) = document.students_form.PhotoPath.value

        call updateRow(students, fieldsArray, values)
        call printStudent(students)
    Else
        call connErrorMsg
    End If
End Sub

' === Students internals ===

Sub printStudent(ByRef rs)
    If (not (rs.BOF and rs.EOF)) Then
        document.students_form.Surname.value = rs("surname")
        document.students_form.Group.value = rs("group")
        document.students_form.Age.value = rs("age")
        document.students_form.Mark.value = rs("mark")
        document.students_form.PhotoPath.value = rs("photo_path")
        document.students_form.Photo.src=rs("photo_path")
    Else
        msgbox("Database is empty!")
        call clearStudentFields
    End If
End Sub



' === Library interface ===

Sub nextBook
    If isConnOpened Then
       call nextRow(library)
       printBook(library)
    Else
       call connErrorMsg
    End If
End Sub

Sub previousBook
    If isConnOpened Then
       call previousRow(library)
       printBook(library)
    Else
       call connErrorMsg
    End If
End Sub

Sub deleteBook
    If isConnOpened Then
        deleteRow(library)
	call nextBook
    Else
        call connErrorMsg
    End If
End Sub

Sub insertBook
    If isConnOpened Then
        Dim fieldsArray(5)
        Dim values(5)
        Dim maxBookID

        fieldsArray(0) = "id"
        fieldsArray(1) = "title"
        fieldsArray(2) = "author"
        fieldsArray(3) = "publication_date"
        fieldsArray(4) = "studID"
        fieldsArray(5) = "association_date"

        ' select max bookId from DB
        maxBookID = request(conn, "SELECT MAX(id) AS id FROM library")

        values(0) = maxBookID("id").value + 1
        values(1) = document.library_form.Title.value
        values(2) = document.library_form.Author.value
        values(3) = document.library_form.PubDate.value
        values(4) = 0
        values(5) = NULL

        call insertRow(library, fieldsArray, values)
        call printBook(library)
    Else
        call connErrorMsg
    End If
End Sub

Sub updateBook
    If isConnOpened Then
        Dim fieldsArray(4)
        Dim values(4)
	Dim assocStud, assocDate

        fieldsArray(0) = "title"
        fieldsArray(1) = "author"
        fieldsArray(2) = "publication_date"
        fieldsArray(3) = "studID"
        fieldsArray(4) = "association_date"

        values(0) = document.library_form.Title.value
        values(1) = document.library_form.Author.value
        values(2) = document.library_form.PubDate.value
	
	assocStud = document.library_form.AssocStud.value
	assocDate = document.library_form.AssocDate.value

	If (assocStud <> "None") Then
           Dim studID
	   studID = getStudIDFromSurname(assocStud)
	   If (studID <> -1) Then 
              values(3) = studID
	      values(4) = assocDate 
	   Else
		msgBox("Please, specify existing student!")
		Exit Sub
	   End If
	Else
	   values(3) = 0
	   values(4) = NULL
	End If

        call updateRow(library, fieldsArray, values)
        call printBook(library)
    Else
        call connErrorMsg
    End If
End Sub

sub showAllBooks
    If isConnOpened Then
        set library = request(conn, "SELECT * FROM library")
        call printBook(library)
    Else
        call connErrorMsg
    End If
End Sub

Sub showBooksOfCurStudent
    If isConnOpened Then
        Dim studID
        studID = students("studID").value
        set library = request(conn, "SELECT * FROM library WHERE studID = " & studID)
        call printBook(library)
    Else
        call connErrorMsg
    End If
End Sub

Sub addBookToStudent
    If isConnOpened Then
        If (library("studID").value = 0) Then
            document.library_form.AssocStud.value = document.students_form.Surname.value
            document.library_form.AssocDate.value = Date
            call updateBook
        Else
            msgBox("Book is busy!")
        End If
    Else
        call connErrorMsg
    End If
End Sub

Sub releaseBook
    If isConnOpened Then
        If (library("studID").value <> 0) Then
	   document.library_form.AssocStud.value = "None"
           document.library_form.AssocDate.value = "None"
	   call updateBook
        End If
    Else
        call connErrorMsg
    End If
End Sub

' === Library internals ===

Function getStudIDFromSurname(studSurname)
    Dim rs
    Set rs = request(conn, "SELECT studID FROM students WHERE surname = '" & studSurname & "'")
    If (not (rs.EOF and rs.BOF)) Then
       getStudIDFromSurname = rs("studID")
    Else
	getStudIDFromSurname = -1
    End If
End Function

Sub printBook(ByRef rs)
    If (not(rs.BOF=True and rs.EOF=True)) Then
        document.library_form.Title.value = rs("title")
        document.library_form.Author.value = rs("author")
        document.library_form.PubDate.value = rs("publication_date")

        If (rs("studID") > 0) Then
            ' Book is associated with student
            Dim assocStud

            ' get student surname with specified id
            assocStud = request(conn, "SELECT surname FROM students WHERE studID =" & rs("studID"))
            document.library_form.AssocStud.value = assocStud("surname")
            document.library_form.AssocDate.value = rs("association_date").value
        Else
            document.library_form.AssocStud.value = "None"
            document.library_form.AssocDate.value = "None"
        End If

	document.library_form.previousBookButton.disabled = False
	document.library_form.nextBookButton.disabled = False
	document.library_form.releaseBookButton.disabled = False
    Else
        msgbox("Book shelf is empty!")
        call clearLibraryFields
	document.library_form.previousBookButton.disabled = True
	document.library_form.nextBookButton.disabled = True
	document.library_form.releaseBookButton.disabled = True
    End If
End Sub

' === Maintanance ===

Sub clearStudentFields
    document.students_form.Surname.value = ""
    document.students_form.Group.value = ""
    document.students_form.Age.value = ""
    document.students_form.Mark.value = ""
    document.students_form.PhotoPath.value = ""
  document.students_form.Photo.src="static/img/default.jpg"
End Sub

Sub clearLibraryFields
    document.library_form.Title.value = ""
    document.library_form.Author.value = ""
    document.library_form.PubDate.value = ""
    document.library_form.AssocStud.value = ""
    document.library_form.AssocDate.value = ""
End Sub

Sub connErrorMsg
    msgBox("Database is closed!")
End Sub