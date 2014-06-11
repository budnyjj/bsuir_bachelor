<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>

<%-- Composition Page: contacts.jsp --%>

<%
request.setAttribute("title", "Связаться с нами");
request.setAttribute("body", "/WEB-INF/content/contacts.jsp");
%>

<jsp:include page="/WEB-INF/templates/html.jsp" />