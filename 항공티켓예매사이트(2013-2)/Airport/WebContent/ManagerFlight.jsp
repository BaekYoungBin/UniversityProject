<%@ page language="java" contentType="text/html; charset=EUC-KR"
    pageEncoding="EUC-KR"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=EUC-KR">
<title>Insert title here</title>
</head>
<body><%@ page import="java.io.*"%>
	<%@ page import="java.sql.*"%>
	<%
		String ID = request.getParameter("ID");
	
		String DB_URL = "jdbc:oracle:thin:@165.132.221.101:1521:XE";
		
	
	%><form action="FlightInsert.jsp" method="POST" >
	<table border='1'  bordercolor = '#AE52IC'>
	<tr>
	<th>비행기종</th><th>출발지</th><th>도착지</th><th>출발 시간</th><th>소요 시간</th><th>비용</th><th>세일</th><th>남은좌석</th><th>선택</th>
	</tr>
	<%
	try{
		DriverManager.registerDriver(new oracle.jdbc.driver.OracleDriver());
		Connection conn = DriverManager.getConnection("jdbc:oracle:thin:@165.132.221.101:1521:XE","db09253072","ghk2xld");
		Statement stmt = conn.createStatement();
		ResultSet rs = stmt.executeQuery("select Plane_Type, Origin, Destination, F_Time, Lead_Time, Cost, leftseat, Sale from flight");
		int i = 0;
		while (rs.next()){
			String Plane_Type = rs.getString("Plane_Type");
			String Origin = rs.getString("Origin");
			String Destination = rs.getString("Destination");
			String F_time = rs.getString("F_Time");
			String Lead_time = rs.getString("Lead_Time");
			String Cost = rs.getString("Cost");
			String Sale = rs.getString("Sale");
			String leftseat = rs.getString("leftseat");
			%>	
			<tr><td><%=Plane_Type%></td><td><%=Origin%></td><td><%=Destination%></td><td><%=F_time %></td><td><%=Lead_time%>
			</td><td><%=Cost %></td><td><%=Sale%></td><td><%=leftseat%></td><td>
			<% if(i == 0){
				%>				
			<input type = "radio" name = "select" value = "<%=i%>" checked>						
				<%
				
			}
			else
			{
%>
				<input type = "radio" name = "select" value = "<%=i%>">			
				<%
			}
			%>
			</td></tr>
			<%	
			i++;
		}
	
	
		rs.close();
		stmt.close();
		conn.close();
	}
	catch (Exception e){
		out.println("Error");
		e.printStackTrace();
	}
	
	
	
	%>
	
	
	</table>	
	<input type="submit" value="수정">
	<input type="hidden" name="ID" value="<%=ID%>">	
	</form>	
	
	<form action="FlightAdd.jsp" method="POST" >
	<input type="hidden" name="ID" value="<%=ID%>">
	<input type="submit" value="추가">		
	</form>	
	
	<form action="ManagerMain.jsp" method="POST">
	<input type="hidden" name="ID" value="<%=ID%>">
	<input type="submit" value="HOME">
	</form>
	<form action="Login.jsp" method="POST" >
	<input type="submit" value="Logout">
	</form>
	<input type = "button" value = "뒤로"	onclick = "history.go(-1)">
</body>
</html>