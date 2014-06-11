<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>

<%-- Composition Page: login.jsp --%>

<%
request.setAttribute("title", "Вход в систему");
request.setAttribute("body", "/WEB-INF/content/login.jsp");
%>

<jsp:include page="/WEB-INF/templates/html.jsp" />