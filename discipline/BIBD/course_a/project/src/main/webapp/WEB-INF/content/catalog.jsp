<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core"%>

<%-- Catalog page content: /WEB-INF/content/catalog.jsp --%>

<div class="list">
  <c:forEach var="bicycle" items="${bicycles}" >
    <a class="list-row" href="${pageContext.request.contextPath}/catalog/detail/${bicycle.id}">
      <div class="list-title">
        <h2>${bicycle.manufacturer} ${bicycle.productName}</h2>
      </div>
      <div class="list-image">
        <img src="${pageContext.request.contextPath}/resources/${bicycle.photoPath}" />
      </div>
      <div class="list-teaser">
        <div class="field">
          <span class="bold">Класс: </span>${bicycle.type}
        </div>
        <div class="field">
          <span class="bold">Год выпуска: </span>${bicycle.year}
        </div>
        <div class="field">
          <span class="bold">Размер рамы: </span>${bicycle.size}
        </div>
        <div class="field">
          <span class="bold">Диаметр колес: </span>${bicycle.wheelsDiameter}
        </div>
        <div class="field">
          <span class="bold">Материал рамы: </span>${bicycle.frameMaterial}
        </div>
        <div class="field">
          <span class="bold">Количество скоростей: </span>${bicycle.ratesNumber}
        </div>
        <div class="field field-price">
          <span class="bold">Цена: </span>${bicycle.price} у. е.
        </div>
      </div>
    </a>
  </c:forEach>
</div>
