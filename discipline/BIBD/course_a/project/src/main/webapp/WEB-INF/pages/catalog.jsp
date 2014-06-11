<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>

<%-- Composition Page: catalog.jsp --%>

<%
request.setAttribute("title", "Welcome to Catalog");
request.setAttribute("body", "/WEB-INF/content/catalog.jsp");
%>

<jsp:include page="/WEB-INF/templates/html.jsp" />