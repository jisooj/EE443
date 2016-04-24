function varargout = lab3_q2_GUI(varargin)
% LAB3_Q2_GUI MATLAB code for lab3_q2_GUI.fig
%      LAB3_Q2_GUI, by itself, creates a new LAB3_Q2_GUI or raises the existing
%      singleton*.
%
%      H = LAB3_Q2_GUI returns the handle to a new LAB3_Q2_GUI or the handle to
%      the existing singleton*.
%
%      LAB3_Q2_GUI('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in LAB3_Q2_GUI.M with the given input arguments.
%
%      LAB3_Q2_GUI('Property','Value',...) creates a new LAB3_Q2_GUI or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before lab3_q2_GUI_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to lab3_q2_GUI_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help lab3_q2_GUI

% Last Modified by GUIDE v2.5 21-Apr-2016 23:19:33

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @lab3_q2_GUI_OpeningFcn, ...
                   'gui_OutputFcn',  @lab3_q2_GUI_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT



% --- Executes just before lab3_q2_GUI is made visible.
function lab3_q2_GUI_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to lab3_q2_GUI (see VARARGIN)

% Choose default command line output for lab3_q2_GUI
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes lab3_q2_GUI wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = lab3_q2_GUI_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;

% --------------------------------------------------------------------


% --- Executes on button press in radiobutton1.
function radiobutton1_Callback(hObject, eventdata, handles)
s = serial('COM6', 'BaudRate',115200);
fopen(s);
fwrite(s, '1');
fclose(s);
delete(s);
operation = 'lowpass filter enabled'



% --- Executes on button press in radiobutton3.
function radiobutton3_Callback(hObject, eventdata, handles)
s = serial('COM6', 'BaudRate',115200);
fopen(s);
fwrite(s, '2');
fclose(s);
delete(s);
operation = 'lowpass filter disabled'


% --- Executes on button press in radiobutton4.
function radiobutton4_Callback(hObject, eventdata, handles)
s = serial('COM6', 'BaudRate',115200);
fopen(s);
fwrite(s, '3');
fclose(s);
delete(s);
operation = 'highpass filter enabled'


% --- Executes on button press in radiobutton5.
function radiobutton5_Callback(hObject, eventdata, handles)
s = serial('COM6', 'BaudRate',115200); 
fopen(s);
fwrite(s, '4');
fclose(s);
delete(s);
operation = 'highpass filter disabled'