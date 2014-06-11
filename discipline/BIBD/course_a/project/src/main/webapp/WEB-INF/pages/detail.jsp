<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>

<%-- Composition Page: detail.jsp --%>

<%
request.setAttribute("title", "Подробно");
request.setAttribute("body", "/WEB-INF/content/detail.jsp");
%>

<jsp:include page="/WEB-INF/templates/no_sidebar.jsp" />