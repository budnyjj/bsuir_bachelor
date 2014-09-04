<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core"%>

<%-- Catalog page content: /WEB-INF/content/order.jsp --%>

<h1>Заказать ${bicycle.manufacturer} ${bicycle.productName}</h1>

<div class="field field-price">
  <span class="bold">Цена: </span>${bicycle.price} у. е.
</div>

<form id="order-form" method="POST" modelAttribute="user" action="${pageContext.request.contextPath}/catalog/${id}/order">
  <div class="user-input">
    <input type="TextField" name="email" placeholder="E-mail..." size=40 />
  </div>
  <div class="user-input">
    <input type="TextField" name="password" placeholder="Пароль..." size=40 />
  </div>
  <div class="user-input">
    <input type="TextField" name="phoneNumber" placeholder="Контактный номер телефона..." size=40 />
  </div>
  <div class="button login-button">
    <input type="submit" value="Подтвердить заказ!" />
  </div>
</form>
