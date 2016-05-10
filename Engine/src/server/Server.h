#pragma once

namespace kubik
{
	enum class RequestStatus
	{
		PROGRESS,
		SUCCESS,
		FAIL,
		HANDLED
	};

	enum class RequestType
	{
		LOGIN,
		PHOTO_UPLOAD,
		SEND_TO_EMAIL
	};

	class Request
	{
	public:
		std::string url;
		RequestStatus success;
		virtual  std::map<std::string, std::string> getMapData()
		{
			using namespace std;
			std::map<std::string, std::string> data;
			return data;
		}

		Request()
		{
			success = RequestStatus::PROGRESS;
		}

		RequestType getType() const
		{
			return type;
		}

		void setHandled()
		{
			success = RequestStatus::HANDLED;
		}

		virtual void setURL(const std::string& url)
		{
			this->url = url;
		}

	protected:
		RequestType type;

	};

	class AuthRequest: public Request
	{
	private:
		std::string user_name = "qwe@qwe.qwe";
		std::string password = "qwertY12+";
		std::string grant_type = "password";
		std::string client_id = "f3d259ddd3ed8ff3843839b";
		std::string client_secret = "4c7f6f8fa93d59c45502c0ae8c4a95b";

	public:
		AuthRequest() 
		{
			type = RequestType::LOGIN;
		}

		virtual std::map<std::string, std::string> getMapData() override
		{
			using namespace std;
			map<string, string> data;
			data.insert(pair<string, string>("username", user_name));
			data.insert(pair<string, string>("password", password));
			data.insert(pair<string, string>("grant_type", grant_type));
			data.insert(pair<string, string>("client_id", client_id));
			data.insert(pair<string, string>("client_secret", client_secret));
			return data;
		}		
	};

	class PostPhotoPhotoBoothRequest : public Request
	{
	public:
		std::string path;
		int photo_id = -1;		
		std::string link = "";
		std::string base64Str;
		int photoHeight;

		PostPhotoPhotoBoothRequest()
		{
			type = RequestType::PHOTO_UPLOAD;
		}

		void setPath(const std::string& path)
		{
			this->path = path;//Paths::getPhotoTemplateRibbonToServerPath();
		}

		void init()
		{
			photo_id = -1;
			link = "";

			ci::DataSourceRef urlRequest = ci::loadFile(path);
			auto loadedTex = ci::gl::Texture(loadImage(urlRequest));
			ci::Buffer bf = ci::Buffer(urlRequest);
			base64Str = toBase64(bf);
			photoHeight = loadedTex.getHeight() / 3;		
		}	

		

		int getHeight() const
		{
			return photoHeight;
		}
	};

	class SendToEmailsRequest : public Request
	{
	public:
		int photo_id = -1;
		int app_id = -1;
		std::string emails = "";

		virtual std::map<std::string, std::string> getMapData() override
		{
			using namespace std;
			map<string, string> data;
			data.insert(pair<string, string>("id", ci::toString(app_id)));
			data.insert(pair<string, string>("photo_id", ci::toString(photo_id)));
			data.insert(pair<string, string>("to", emails));	
			return data;
		}
	};

	class StandInfoRequest : public Request
	{
	//public:

	};

	class PhotoPrintRequest : public Request
	{
	public:
		int appID;
		int photo_id;
		std::string photo_url;
		std::string hashtag;

		virtual std::map<std::string, std::string> getMapData() override
		{
			using namespace std;
			map<string, string> data;
			data.insert(pair<string, string>("appID", ci::toString(appID)));

			if (photo_id != -1)
				data.insert(pair<string, string>("photo_id", ci::toString(photo_id)));

			if (photo_url != "")
				data.insert(pair<string, string>("photo_url", photo_url));

			if (hashtag != "")
				data.insert(pair<string, string>("hashtag", hashtag));

			return data;
		}
	};

	

	typedef std::shared_ptr<class PhotoPrintRequest> PhotoPrintRequestRef;
	typedef std::shared_ptr<class SendToEmailsRequest> SendToEmailsRequestRef;
	typedef std::shared_ptr<class PostPhotoPhotoBoothRequest> PostPhotoPhotoBoothRequestRef;
	typedef std::shared_ptr<class AuthRequest> AuthRequestRef;
	typedef std::shared_ptr<class StandInfoRequest> StandInfoRequestRef;
	typedef std::shared_ptr<class Request> RequestRef;

	class Server
	{
	public:
		static Server& getInstance()
		{
			static Server server;
			return server;
		};	

		void login();
		void init();

		void standInfo();
		void postPhoto(const std::string& path, const std::string& appID);
		void sendToEmails(int appID, int photoID, const std::string& emails);
		void photoPrint(int appID, int photo_id = -1, const std::string& photo_url = "", const std::string& hashtag = "");
	
		boost::signals2::signal<void()> loginSuccess;
		boost::signals2::signal<void(const std::string& photo_id, const std::string& link)> photoUploadSuccess;
		boost::signals2::signal<void()> photoUploadError;

	private:
		std::string access_token;
		std::string SERVER = "http://hypercubic.familyagency.ru";	

		ThreadRef mediaLoadThread;

		bool isLogin, threadLoad;
	
		void threadLogin(const AuthRequestRef& request);
		void threadPostPhoto(const PostPhotoPhotoBoothRequestRef& request);
		void threadStandInfo(const StandInfoRequestRef& request);
		void threadSendToEmails(const SendToEmailsRequestRef& request);
		void threadPhotoPrint(const PhotoPrintRequestRef& request);

		void update();	
		bool checkLogin();

		int errorCount;			
		void addToQue(const RequestRef& request);		

		RequestRef currentRequest;
	};

	inline Server& server()
	{
		return Server::getInstance();
	};
}