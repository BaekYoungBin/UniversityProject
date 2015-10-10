<%@ page language="java" contentType="text/html; charset=EUC-KR"
    pageEncoding="EUC-KR"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=EUC-KR">
<title>Insert title here</title>
</head>
<body>
<%String ID = request.getParameter("ID"); %>
				<form action="ManagerFlight.jsp" method="POST" >
				<input type="hidden" name="ID" value="<%=ID%>">
				<input type="submit" value="항공편 검색/수정">				
				</form>	
				<form action="Login.jsp" method="POST" >
				<input type="submit" value="Logout">
				</form>	
				
			

</body>
</html>