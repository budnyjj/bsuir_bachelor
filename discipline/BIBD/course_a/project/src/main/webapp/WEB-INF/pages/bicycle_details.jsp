<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>

<%-- Composition Page: bicycle_details.jsp --%>

<%
request.setAttribute("title", "Информация о велосипеде");
request.setAttribute("body", "/WEB-INF/content/bicycle_details.jsp");
%>

<jsp:include page="/WEB-INF/templates/no_sidebar.jsp" />