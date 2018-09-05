﻿Param( [String]$Att, [String]$Subj, [String]$Body)

Function Send-EMail{    
Param (      
            [Parameter(`
            Mandatory=$true)]       
    [String]$To, 
            [Parameter(`
            Mandatory=$true)]
    [String]$From, 
            [Parameter(`
            Mandatory=$true)]
    [String]$Password, 
            [Parameter(`
            Mandatory=$true)]
    [String]$Subject, 
            [Parameter(`
            Mandatory=$true)]
    [String]$Body, 
            [Parameter(`
            Mandatory=$true)]
    [String]$attachment  
    )

try{    
    $Msg = New-Object System.Net.Mail.MailMessage($From, $To, $Subject, $Body)
    Srv = \"smtp.gmail.com\" 
    if ($attachment -ne $null) {
        try {
            $Attachments = $attachment -split (\"\\:\\:\");
        
            ForEach ($val in $Attachments)
            {
                $attch = New-Object System.Net.Mail.Attachment($val)
                $Msg.Attachments.Add($attch)    
            }                
        }
        catch{                       
            exit 2; 
        }   
        
        $Client = New-Object Net.Mail.SmtpClient($Srv, 587)     
        $Client.EnableSsl = $true
        $Client.Credentials = New-Object System.Net.NetworkCredential($From.Split("0")[0], $Password);
        $Client.Send($Msg)
        Remove-Variable -Name Client
        Remove-Variable -Name Password
        exit 7;
    }
}     
catch          
    {            
    exit 3; 
    }
} #End Function Send-EMail
         
try {
    Send-EMail 
        -attachment $Att 
        -To "richard.a.anderson@gmail.com"  
        -Body $Body 
        -Subject $Subj 
        -password "HardCore22@@"
        -From "richard.a.anderson@gmail.com"
}
catch{
    exit 4;
}

