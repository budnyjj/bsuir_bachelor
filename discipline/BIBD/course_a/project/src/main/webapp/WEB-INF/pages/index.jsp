<?xml version="1.0" encoding="ISO-8859-1" ?>
<%@ page language="java" contentType="text/html; ISO-8859-1" pageEncoding="iso-8859-1" %>
<!DOCTYPE html>
<html lang="en">

<head>
    <title>Test jsp</title>
</head>

<body>

<p>
    ${message}<br/>
    <a href="${pageContext.request.contextPath}/user/add.html">Add new user</a>
    <a href="${pageContext.request.contextPath}/user/list.html">User's list</a>
</p>

</body>
</html>