
clear all
close all

Nm=1;

c=10;

eps=sqrt(c);

T=5000;
dt=0.001;

Nt=floor(T/dt);

% Nt=2^nextpow2(floor(T/dt));
% T=dt*Nt;

Tr=[1:T];
lTr=Tr/dt;
NTr=numel(Tr);

t=[0:dt:T];
x=zeros(Nm,Nt+1);

x(:,1)=randn(Nm,1);

for im=1:Nm


	 disp('STARTING SIMULATION');
fflush(stdout);
    for it=1:Nt

        x(im,it+1)=x(im,it)-x(im,it)*dt+eps*randn(1,1)*sqrt(dt);

    end
    
   

end

    disp('END OF SIMULATION');
fflush(stdout);
    
% STATICAL PROPERTIES FOR THE REALISATION
varX = var(x(1,:).^2);
Xbar = mean(x(1,:).^2);

% LOOPS ON POSSIBLE BUNCH LENGTHS

% nblckvec=floor(2.^[4:9]);
% 
% nblckpmin =  min(nblckvec);
% nblckpmax =  max(nblckvec);

nblckpmin=100;
nblckpmax=5000;

tau=zeros(Nm,nblckpmax-nblckpmin+1);
tau_var=zeros(Nm,nblckpmax-nblckpmin+1);

pvec=zeros(1,nblckpmax-nblckpmin+1);

for im=1:Nm

% p= number of points inside each block
% nblckp= Nt/p = number f blocks
  
	 for nblckp=nblckpmin:nblckpmax % nblckp : NUMBER OF POINTS IN A BLOCK
		      disp(nblckp);
fflush(stdout);
    p=floor(Nt/nblckp); % NUMBER OF BLOCKS
    pvec(nblckp-nblckpmin+1)=p;
    
    for ip=1:nblckp
       
        E=(dt*(sum(x(im,1+(ip-1)*p:ip*p).^2) - Xbar*p)).^2;
        
        tau(im,nblckp-nblckpmin+1) = tau(im,nblckp-nblckpmin+1) + E;
        
    end
    
    tau(im,nblckp-nblckpmin+1) = tau(im,nblckp-nblckpmin+1)/(2*varX*p*dt*nblckp);
            
end

end
    

figure(1)

plot(t,x(1,:))


figure(2)

xr=linspace(min(min(x)),max(max(x)),floor(sqrt(Nt)));
dxr=xr(2)-xr(1);

[px,xr]=hist(x,xr);
px=px/sum(px*dxr);

plot(xr,px)
hold
plot(xr,exp(-(xr.^2)/c)/sqrt(pi*c),'r')


figure(3)
xlabel('Duration of each time chunk')
ylabel('$\tau_c^{(p)}')
plot(pvec*dt,tau)
xlabel('$p\delta t$');
ylabel('$\tau^{(p)}');
print -depslatex 'tau_dT.tex'

