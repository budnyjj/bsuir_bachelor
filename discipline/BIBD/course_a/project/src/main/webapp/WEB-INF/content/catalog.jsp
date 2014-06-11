<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core"%>

<%-- Catalog page content: /WEB-INF/content/catalog.jsp --%>

<div class="list">
  <c:forEach var="bicycle" items="${bicycles}" >
    <div class="list-row">
      <div class="list-title">
        <h2>${bicycle.manufacturer} ${bicycle.productName} (${bicycle.year})</h2>
      </div>
      <div class="list-image">
        <img src="${pageContext.request.contextPath}/resources/${bicycle.photoPath}" />
      </div>
      <div class="list-teaser">
        <div>${bicycle.type}</div>
        <div>${bicycle.size}</div>
        <div>${bicycle.price}</div>
        <div><a href="${pageContext.request.contextPath}/catalog/detail/${bicycle.id}">detail</a></div>
      </div>
    </div>
  </c:forEach>
</div>
