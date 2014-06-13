<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>

<%-- Composition Page: order.jsp --%>

<%
request.setAttribute("title", "Подтвердить заказ");
request.setAttribute("body", "/WEB-INF/content/order.jsp");
%>

<jsp:include page="/WEB-INF/templates/no_sidebar.jsp" />