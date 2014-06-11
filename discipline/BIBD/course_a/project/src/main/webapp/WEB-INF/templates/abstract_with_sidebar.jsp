<%-- Abstract Layout: /WEB-INF/templates/abstract.jsp --%> 
<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
  <meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
  <link type="text/css" rel="stylesheet" href="${pageContext.request.contextPath}/resources/css/common.css" />
  <link type="text/css" rel="stylesheet" href="${pageContext.request.contextPath}/resources/css/custom.css" />
  <title> ${requestScope.title} </title>
</head>
<body>
  <div class="wrap">
    <div class="header">
      <jsp:include page="${requestScope.header}" />
    </div>
    
    <div class="menu">
      <jsp:include page="${requestScope.menu}" />
    </div>

    <div class="container-2 content">
      <jsp:include page="${requestScope.body}" />  
    </div>

    <div class="container-1 sidebar">
      <jsp:include page="${requestScope.sidebar}" />  
    </div>

    <div class="footer">
      <jsp:include page="${requestScope.footer}" />
    </div>
  </div>
</body>
</html>
