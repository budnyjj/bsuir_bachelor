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
    <thead>
    <tr>
        <td>Product name</td>
        <td>Manufacturer</td>
        <td>Type</td>
        <td>Size</td>
        <td>Price</td>
        <td>Details</td>
    </tr>
    </thead>
    <tbody>
    <c:forEach var="bicycle" items="${bicycles}" >
    <tr>
        <td>${bicycle.productName}</td>
        <td>${bicycle.manufacturer}</td>
        <td>${bicycle.type}</td>
        <td>${bicycle.size}</td>
        <td>${bicycle.price}</td>
        <td><a href="${pageContext.request.contextPath}/catalog/detail/${bicycle.id}">detail</a></td>
    </tr>
    </c:forEach>
    </tbody>
</table>

<p><a href="${pageContext.request.contextPath}/catalog">Catalog page</a></p>

</body>
</html>