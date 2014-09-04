<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>

<%-- Composition Page: orders.jsp --%>

<%
request.setAttribute("title", "Заказы, ожидающие обработки");
request.setAttribute("body", "/WEB-INF/content/orders.jsp");
%>

<jsp:include page="/WEB-INF/templates/no_sidebar.jsp" />