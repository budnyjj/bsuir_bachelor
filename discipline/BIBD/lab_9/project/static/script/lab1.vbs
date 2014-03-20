Option Explicit
Dim conn, strConnection, strDataBase, rs

Sub openConnection
	Set conn = CreateObject("ADODB.Connection")
        Set rs = CreateObject("ADODB.Recordset")
	strConnection = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source="
	strDataBase = "C:\dev\BIBD\lab_9\db\my.mdb"

	conn.Open strConnection & strDataBase


        rs.Open "SELECT * FROM students", conn, 2

	document.main_form.tFIO.value=rs("fio")
	document.main_form.tAge.value=rs("age")
        document.avatar.src=rs("imagePath")
End Sub

Sub getNext
	if rs.EOF = false then
		rs.moveNext
		if rs.EOF=true then
			rs.moveFirst
		end if
 	else
		rs.moveFirst
	end if

	document.main_form.tFIO.value=rs("fio")
	document.main_form.tAge.value=rs("age")
        document.avatar.src=rs("imagePath")
End Sub

Sub getPrevious
	if rs.BOF = false then
		rs.movePrevious
		if rs.BOF=true then
			rs.moveLast
		end if
	else
		rs.moveLast
	end if

	document.main_form.tFIO.value=rs("fio")
	document.main_form.tAge.value=rs("age")
        document.avatar.src=rs("imagePath")
End Sub

Sub find
	Dim sq

        if rs.State = 1 then
             rs.Close
        end if

	sq = "SELECT * FROM students where fio=""" + document.main_form.tFIO.value+""""

	rs.Open sq, conn

	document.main_form.tFIO.value = rs("fio")
	document.main_form.tAge.value = rs("age")
        document.avatar.src=rs("imagePath")
End Sub

Sub insertRecord
        rs.Open "SELECT MAX(id) AS maxID FROM students", conn

        Dim maxID
        maxID = rs("maxID")
End Sub

Sub deleteRecord

End Sub
