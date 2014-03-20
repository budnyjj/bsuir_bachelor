Option Explicit

Sub printStudent(ByRef rs)
	document.main_form.Surname.value = rs("surname")
	document.main_form.Group.value = rs("group")
	document.main_form.Age.value = rs("age")
	document.main_form.Mark.value = rs("mark")
	document.main_form.PhotoPath.value = rs("photo_path")
        document.main_form.Photo.src=rs("photo_path")
End Sub

Sub nextStudent

End Sub

Sub previousStudent

End Sub

