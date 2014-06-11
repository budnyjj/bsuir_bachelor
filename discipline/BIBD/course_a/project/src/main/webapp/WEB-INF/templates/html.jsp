<%-- Top-level template: /WEB-INF/templates/html.jsp --%> 
<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>

<%
request.setAttribute("header", "/WEB-INF/templates/header.jsp");
request.setAttribute("menu", "/WEB-INF/templates/menu.jsp");
request.setAttribute("footer", "/WEB-INF/templates/footer.jsp");
%>

<%@ include file="/WEB-INF/templates/abstract.jsp" %>