<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core"%>

<h1>${user.name}</h1>

<div class="list">
  <c:forEach var="bicycle" items="${bicycles}" >
    <a class="list-row" href="${pageContext.request.contextPath}/catalog/${bicycle.id}">
      <div class="list-title">
        <h2>${bicycle.manufacturer} ${bicycle.productName}</h2>
      </div>
      <div class="field field-price">
        <span class="bold">Цена: </span>${bicycle.price} у. е.
      </div>
    </a>
  </c:forEach>
</div>
