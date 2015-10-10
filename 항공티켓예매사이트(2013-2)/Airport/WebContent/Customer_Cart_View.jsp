<%@ page language="java" contentType="text/html; charset=EUC-KR"
    pageEncoding="EUC-KR"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=EUC-KR">
<title>Insert title here</title>
</head>
<body>
	<%@ page import="java.io.*"%>
	<%@ page import="java.sql.*"%>
	<%
	String ID = request.getParameter("ID");
	out.print(ID);
	String DB_URL = "jdbc:oracle:thin:@165.132.221.101:1521:XE";	
	%><form action="Customer_Cart_continue.jsp" method="POST" >
	<table border='1'  bordercolor = '#AE52IC'>
	<tr>
	<th>ID</th><th>비행기종</th><th>출발지</th><th>도착지</th><th>비용</th><th>선택</th><th>
	</tr>
	<%
	String TotalCost;
	int TotalCostInt= 0;
	
	try{
		DriverManager.registerDriver(new oracle.jdbc.driver.OracleDriver());
		Connection conn = DriverManager.getConnection("jdbc:oracle:thin:@165.132.221.101:1521:XE","db09253072","ghk2xld");
		Statement stmt = conn.createStatement();
		ResultSet rs = stmt.executeQuery("select C_ID, Plane_type, Origin, Destination, Cost from customer_cart where c_id = '"+ID+"'");
	
		int i = 0;
		while (rs.next()){		
			String C_ID = rs.getString("C_ID");
			String Plane_Type = rs.getString("Plane_Type");
			String Origin = rs.getString("Origin");
			String Destination = rs.getString("Destination");
			String Cost = rs.getString("Cost");
			int CostInt = Integer.valueOf(Cost);
			TotalCostInt = TotalCostInt + CostInt;
			%>	
			<tr><td><%=C_ID %></td><td><%=Plane_Type%></td><td><%=Origin%></td><td><%=Destination%></td>
			<td><%=Cost %></td><td>
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
		TotalCost = String.valueOf(TotalCostInt);
		%>
		<tr><td>총비용</td><td></td><td></td><td></td><td><%=TotalCost%></td></tr>	
		<%
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
	<input type="hidden" name="ID" value="<%=ID%>">	
	<input type="submit" value="선택">	
	</form>	
	
	<input type = "button" value = "뒤로가기"  onclick = "history.go(-1)">
<form action="CustomerMain.jsp" method="POST">
<input type="hidden" name="ID" value="<%=ID%>">
<input type="submit" value="HOME">
</form>
	<form action="Login.jsp" method="POST" >
	<input type="submit" value="Logout">
	</form>
</body>
</html>