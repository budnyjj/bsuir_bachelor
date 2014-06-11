<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>

<%-- Composition Page: catalog.jsp --%>

<%
request.setAttribute("title", "Каталог");
request.setAttribute("body", "/WEB-INF/content/catalog.jsp");
request.setAttribute("sidebar", "/WEB-INF/content/catalog-sidebar.jsp");
%>

<jsp:include page="/WEB-INF/templates/with_sidebar.jsp" />