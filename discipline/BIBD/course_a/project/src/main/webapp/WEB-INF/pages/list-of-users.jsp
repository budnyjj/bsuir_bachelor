<%@taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>

<?xml version="1.0" encoding="ISO-8859-1" ?>

<%@page language="java" contentType="text/html; ISO-8859-1" pageEncoding="iso-8859-1" %>

<html>
<head>
    <meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1>" />
    <title>User's list</title>
</head>

<body>

<p>Here you can add see list of the users</p>

<table>
    <thead>
        <tr>
            <th>id</th>
            <th>email</th>
            <th>name</th>
            <th>phone number</th>
            <th>role</th>
            <th>delete</th>
        </tr>
    </thead>

    <tbody>
    <c:forEach var="user" items="${users}">
        <tr>
            <td>${user.id}</td>
            <td>${user.email}</td>
            <td>${user.name}</td>
            <td>${user.phoneNumber}</td>
            <td>${user.role}</td>
            <td><a href="${pageContext.request.contextPath}/user/delete/${user.id}.html">Delete</a></td>
        </tr>
    </c:forEach>
    </tbody>
</table>


<p><a href="${pageContext.request.contextPath}/index.html">Home page</a></p>

</body>
</html>