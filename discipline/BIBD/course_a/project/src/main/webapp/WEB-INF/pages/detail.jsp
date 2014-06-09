<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>

<?xml version="1.0" encoding="ISO-8859-1" ?>
<%@page language="java" contentType="text/html; ISO-8859-1" pageEncoding="ISO-8859-1" %>
<!DOCTYPE html>

<html>
<head>
    <meta http-equiv="Content-Type" content="text/html;" charset="iso-8859-1>" />
</head>

<body>

<table>
    <tbody>
    <tr>
        <td>Product name:</td>
        <td>${bicycle.productName}</td>
    </tr>
    <tr>
        <td>Manufacturer:</td>
        <td>${bicycle.manufacturer}</td>
    </tr>
    <tr>
        <td>Type:</td>
        <td>${bicycle.type}</td>
    </tr>
    <tr>
        <td>Size:</td>
        <td>${bicycle.size}</td>
    </tr>
    <tr>
        <td>Price:</td>
        <td>${bicycle.price}</td>
    </tr>
    </tbody>
</table>

<p><a href="${pageContext.request.contextPath}/catalog">Catalog page</a></p>

</body>
</html>