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
	String Plane_Type = request.getParameter("Plane_Type");
	String I_Origin = request.getParameter("Origin");
	String I_Destination = request.getParameter("Destination");
	String I_F_Time = request.getParameter("F_Time");
	String I_Lead_Time = request.getParameter("Lead_Time");
	String I_Cost = request.getParameter("Cost");
	String I_Sale = request.getParameter("Sale");
	String I_leftseat = request.getParameter("leftseat");
	String DB_URL = "jdbc:oracle:thin:@165.132.221.101:1521:XE";
	
	 if(I_Origin.length() > 10 || I_Origin.length() <1)
		{
			out.print("출발지를 확인해주세요");
			%>
				<input type = "button" value = "확인"
						onclick = "history.go(-1)">
			<%
		}
		else if(I_Destination.length() >10 || I_Destination.length() <1)
		{
			out.print("도착지를 확인해주세요");
			%>
				<input type = "button" value = "확인"
						onclick = "history.go(-1)">
			<%
		}
		else if(I_F_Time.length() > 20 || I_F_Time.length() <1)
		{
			out.print("출발시간을 확인해주세요");
			%>
				<input type = "button" value = "확인"
						onclick = "history.go(-1)">
			<%
		}
		else if(I_Lead_Time.length()>20 || I_Lead_Time.length()<1)
		{
			out.print("소요시간을 확인해주세요");
			%>
				<input type = "button" value = "확인"
						onclick = "history.go(-1)">
			<%
		}
		else if(I_Cost.length() > 10 || I_Cost.length()<1)
		{
			out.print("가격을 확인해주세요");
			%>
				<input type = "button" value = "확인"
						onclick = "history.go(-1)">
			<%
		}
		else if(I_Sale.length() > 3 || I_Sale.length()<1)
		{
			out.print("세일율을 확인해주세요");
			%>
				<input type = "button" value = "확인"
						onclick = "history.go(-1)">
			<%
		}else if(I_leftseat.length() > 3 || I_Sale.length()<1)
		{
			out.print("탑승인원이너무많습니다.");
			%>
				<input type = "button" value = "확인"
						onclick = "history.go(-1)">
			<%
		}
	try{
		
				
			DriverManager.registerDriver(new oracle.jdbc.driver.OracleDriver());
			Connection conn = DriverManager.getConnection("jdbc:oracle:thin:@165.132.221.101:1521:XE","db09253072","ghk2xld");
			Statement stmt = conn.createStatement();
			ResultSet rs;			
				rs = stmt.executeQuery("update FLIGHT set Origin = '"+I_Origin +"' where Plane_Type = '" + Plane_Type +"'");
				rs = stmt.executeQuery("update FLIGHT set Destination = '"+I_Destination +"' where Plane_Type = '" + Plane_Type +"'");
				rs = stmt.executeQuery("update FLIGHT set F_Time = '"+I_F_Time +"' where Plane_Type = '" + Plane_Type +"'");
				rs = stmt.executeQuery("update FLIGHT set Lead_Time = '"+I_Lead_Time +"' where Plane_Type = '" + Plane_Type +"'");
				rs = stmt.executeQuery("update FLIGHT set Cost = '"+I_Cost +"' where Plane_Type = '" + Plane_Type +"'");
				rs = stmt.executeQuery("update FLIGHT set Sale = '"+I_Sale +"' where Plane_Type = '" + Plane_Type +"'");
				rs = stmt.executeQuery("update FLIGHT set leftseat = '"+I_leftseat +"' where Plane_Type = '" + Plane_Type +"'");
			 rs.close();
			stmt.close();
			conn.close();
			
	}
	catch(Exception e) {
		e.printStackTrace();
	}
		
		
		
		
		
		%>
		
		<form action="ManagerMain.jsp" method="POST">
		
<input type="hidden" name="ID" value="<%=ID%>">
<input type="submit" value="HOME">
</form>
</body>
</html>