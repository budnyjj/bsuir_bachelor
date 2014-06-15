<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>

<%-- Composition Page: user_details.jsp --%>

<%
request.setAttribute("title", "Страница пользователя");
request.setAttribute("body", "/WEB-INF/content/user_details.jsp");
%>

<jsp:include page="/WEB-INF/templates/no_sidebar.jsp" />