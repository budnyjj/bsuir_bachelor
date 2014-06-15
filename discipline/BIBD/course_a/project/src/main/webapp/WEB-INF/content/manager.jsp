<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core"%>

<h1>Заказы, ожидающие обработки</h1>

<c:choose>
  <c:when test="${(orders.isEmpty())}">
    Заказы отcутствуют!
  </c:when>
  <c:otherwise>

    <table class="detail-parameters">
      <thead>
        <tr>
          <th class="flush-left">
            Название товара
          </th>
          <th class="flush-left">
            Цена
          </th>
          <th class="flush-left">
            Дата заказа
          </th>
          <th class="flush-left">
            Имя
          </th>
          <th class="flush-left">
            Телефон
          </th>
          <th class="flush-left">
            Обработка
          </th>
        </tr>
      </thead>
      <tbody>
        <c:forEach var="order" items="${orders}" >
          <c:set var="bicycle" scope="session" value="${order.bicycle}"/>
          <c:set var="user" scope="session" value="${order.user}"/>
          <tr>
            <td class="flush-left">
              <a class="brown-text" href="${pageContext.request.contextPath}/catalog/${bicycle.id}">
                ${bicycle.manufacturer} ${bicycle.productName}
              </a>
            </td>
            <td class="flush-left">${order.goodsCost}</td>
            <td class="flush-left">${order.orderDate}</td>
            <td class="flush-left">${user.name}</td>
            <td class="flush-left">${user.phoneNumber}</td>
            <td class="flush-left">
                <a class="button approve-button" href="#">Подтвердить</a> 
                <a class="button discard-button" href="#">Отменить</a> 
            </td>
          </tr>
        </c:forEach>
      </tbody>
    </table>

  </c:otherwise>
</c:choose>

