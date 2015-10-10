<%@ page language="java" contentType="text/html; charset=EUC-KR"
    pageEncoding="EUC-KR"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=EUC-KR">
<title>로그인 체크</title>
</head>
<body>
<%@ page import = "java.io.*" %>
	<%@ page import = "java.sql.*" %>
<%
	String tmpID = request.getParameter("ID");
	String tmpPassword = request.getParameter("pwd");
	String C_ID = "null";
	String C_PS = "null";
	String C_Name = "null";
	String C_Age;
	String C_Gender;
	String C_address;
	String C_PhoneNumbr;
	String C_Rank;
	String C_Mileage;
	String M_ID = "null";
	String M_PS = "null";
	String M_Name = "null";
	String A_ID = "null";
	String A_PS = "null";
	String A_Name = "null";
	String E_ID = "null";
	String E_PS = "null";
	String E_Name = "null";
	String result = new String();
	result = (String)request.getParameter("LoginType");

%>


<%
	String DB_URL = "jdbc:oracle:thin:@165.132.221.101:1521:XE";
	try{
		DriverManager.registerDriver(new oracle.jdbc.driver.OracleDriver());
		Connection conn = DriverManager.getConnection("jdbc:oracle:thin:@165.132.221.101:1521:XE","db09253072","ghk2xld");
		Statement stmt = conn.createStatement();
		ResultSet rs ;
		if(result.equals("Customer"))
		{
			 rs = stmt.executeQuery("select * from CUSTOMER where C_ID = '" + tmpID +"'");
			 while(rs.next())
				{
					C_ID = rs.getString("C_ID");
					C_PS = rs.getString("C_PS");
					C_Name = new String(rs.getString("C_NAME").getBytes("8859_1"));				
				}					
			
				if(tmpID.length() > 20)
				{
					out.print("Too long ID");
				}
				else if(C_ID == "null")
				{
					out.print("아이디를 확인해주세요");
					%>
					<input type = "button" value = "확인"
							onclick = "history.go(-1)">
				<%}		
				else if(!tmpPassword.equals(C_PS))
				{
					out.print("비밀번호가 틀렸습니다.");
				%>	<input type = "button" value = "확인"
							onclick = "history.go(-1)">
					<%
				}
				else
				{
					out.print(C_Name + "님이 로그인하셨습니다.");
					%>
				<form action="CustomerMain.jsp" method="POST" >
				<input type="hidden" name="ID" value="<%=tmpID%>">
				<input type="submit" value="확인">				
				</form>	
				<% 
				}	
				rs.close();
				stmt.close();
				conn.close();
		}
		
		else if(result.equals("Manager"))
		{
			rs = stmt.executeQuery("select * from MANAGER where M_ID = '" + tmpID + "'");
			while(rs.next()){
				M_ID = rs.getString("M_ID");
				M_PS = rs.getString("M_PS");
				M_Name = new String(rs.getString("M_NAME").getBytes("8859_1"));
			}
			
			if(tmpID.length() > 20)
			{
				out.print("Too long ID");
				%>
					<input type = "button" value = "확인"
							onclick = "history.go(-1)">
				<%
			}
			else if(M_ID == "null")
			{
				out.print("아이디를 확인해주세요");
				%>
					<input type = "button" value = "확인"
							onclick = "history.go(-1)">
				<%
			}
			else if(!tmpPassword.equals(M_PS))
			{
				out.print("비밀번호를 확인해주세요");
				%>
					<input type = "button" value = "확인"
							onclick = "history.go(-1)">
				<%
			}
			else
			{
				out.print("관리자 로그인 완료.");
				%>
				<form action="ManagerMain.jsp" method="POST" >
				<input type="hidden" name="ID" value="<%=M_ID%>">
				<input type="submit" value="확인">				
				</form>	
			
				<%
			}
			rs.close();
			stmt.close();
			conn.close();
		}
		else if(result.equals("Agency")){
			rs = stmt.executeQuery("select * from AGENCY where A_ID = '" + tmpID + "'");		
			while(rs.next()){
				A_ID = rs.getString("A_ID");
				A_PS = rs.getString("A_PS");
				A_Name = rs.getString("A_Name");
			}
			if(tmpID.length() > 20)
			{
				out.print("Too long ID");
				%>
					<input type = "button" value = "확인"
							onclick = "history.go(-1)">
				<%
			}
			else if(A_ID == "null")
			{
				out.print("아이디를 확인해주세요");
				%>
					<input type = "button" value = "확인"
							onclick = "history.go(-1)">
				<%
			}
			else if(!tmpPassword.equals(A_PS))
			{
				out.print("비밀번호를 확인해주세요");
				%>
				<input type = "button" value = "확인"
						onclick = "history.go(-1)">
			<%
			}
			else
			{
				out.print("여행사 로그인 완료");
				%>
				
				<form action="AgencyMain.jsp" method="POST" >
				<input type="hidden" name="ID" value="<%=A_ID%>">
				<input type="submit" value="확인">				
				</form>	
				<input type = "button" value = "Logout"
				onclick = "history.go(-1)">
			
			<%}
			rs.close();
			stmt.close();
			conn.close();
		}
		else if(result.equals("Employee")){
			rs = stmt.executeQuery("select * from EMPLOYEE where E_ID = '" + tmpID + "'");
			
			while(rs.next()){
				E_ID = rs.getString("E_ID");
				E_PS = rs.getString("E_PS");
				E_Name = rs.getString("E_Name");
			}
			
			if(tmpID.length() > 20)
			{
				out.print("Too long ID");
				%>
				<input type = "button" value = "확인"
						onclick = "history.go(-1)">
			<%
			}
			else if(E_ID == "null")
			{
				out.print("아이디를 확인해주세요");
				%>
				<input type = "button" value = "확인"
						onclick = "history.go(-1)">
			<%
			}
			else if(!tmpPassword.equals(E_PS))
			{
				out.print("비밀번호를 확인해주세요");
				%>
				<input type = "button" value = "확인"
						onclick = "history.go(-1)">
			<%
			}
			else
			{
				out.print("항공사직원 로그인 완료");
				%>
			
				<form action="EmployeeMain.jsp" method="POST" >
				<input type="hidden" name="ID" value="<%=E_ID%>">
				<input type="submit" value="확인">				
				</form>	
				<input type = "button" value = "Logout"
				onclick = "history.go(-1)">
			
			<%
			}
			rs.close();
			stmt.close();
			conn.close();
		}	
		
	}
	
	catch(Exception e) {
		e.printStackTrace();
	}
		
		
		%>
	
</body>
</html>